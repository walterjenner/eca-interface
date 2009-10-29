<?php 
  //the path to all media files
  define("MEDIA_PATH", "http://localhost/www/eca/public/");
  define("URL_LENGTH", 45);
  define("DO_AGENT_SYNC", TRUE);
  define("DO_ARTWORK_SYNC", TRUE);
  define("DO_EXHIBITION_SYNC", FALSE);
  define("NODE_SYNC_INTERVAL", (60 * 60 * 24) );  // 1 day
  define("MIN_CACHE_LIFETIME", (60 * 60 * 24) );  // 1 day. that means that before the item in cache is one day old, 
                                                  // it will NOT be remove, by cache_clear_all()!
                                                  // As cache_clear_all() is called daily, the maximum time
                                                  // an update in the compart db needs to be visible is TWO DAYS!
  
  global $userMapping;
  $userMapping = array( 1000014 => 5,
                        1000016 => 5, //j�rn
                        1000019 => 6, //cordesh
                        1000020 => 4, //nake
                        1000022 => 7, //jes
                        1000023 => 8, //susi
                        1000031 => 9);
  
  //the folders where certain file types are stored
  global $formatFolder;
  $formatFolder = array('png' => "imageUploads", 
                        'jpg' => "imageUploads", 
                        'gif' => "imageUploads",
                        'tif' => "imageUploads",
                        'flv' => "videoUploads", 
                        'mp3' => "soundUploads",
                        'pdf' => "docUploads" );
  
  /*
   * get an array with all media from the db
   */
  function eca_get_media($table_id, $row_id){    
    
    $selectMedia = "SELECT mf.file_name, mf.format, mf.description FROM compartdb.illustrated_by LEFT JOIN compartdb.media_file mf ON illustrated_by.media_file_id = mf.media_file_id WHERE illustrated_by.row_id = $row_id AND illustrated_by.table_id = $table_id";
    $resultMedia = db_query($selectMedia);
    $media = array();
    while ($dataMedia = db_fetch_object($resultMedia)) {
      array_push($media, $dataMedia);
    }
    //ensure that the first media is an image
    if( !eca_is_image( $media[0] ) ){
      for($i = 0; $i < count($media); $i++){
        if(eca_is_image( $media[$i] )){
          $temp = $media[0];
          $media[0]= $media[$i];
          $media[$i] = $temp;
          break;
        }
      }
    }    
    
    return $media;
  }
  
  /*
   * return a markup-snippet to embed a media file
   */
  function eca_get_media_markup($media, $size){
    $path = eca_get_media_path($media->format, $size);
    if($size != '' && eca_is_image($media)) //note: seems like all thumbs and medium images are jpg's
      $path .= $media->file_name . '.' . jpg;
    else
      $path .= $media->file_name . '.' . $media->format;
    $output = "";
    if( eca_is_image($media) )
    {
      $output .= "<div>";
      $output .= "<img src=\"$path\" alt=\"$media->file_name\" />";
      $output .= "<br/>$media->description</div>";
      return $output;
    }
    else if($media->format == 'pdf'){
      return "<a href=\"$path\" title=\"Download $media->file_name\">$media->file_name.$media->format</a>";
    }
    else if($media->format == 'flv' || $media->format == 'mp3')
    {
      return "<a href=\"$path\" title=\"Download $media->file_name\">$media->file_name</a>";
    }
    else 
    {
      return $media->format . ':' . $media->file_name;
    }
  }
  
  function eca_is_image($media){
    return ($media->format == 'jpg' || $media->format == 'gif' || $media->format == 'png' || $media->format == 'tif');
  }
  
  /*
   * get the path for a certain file type
   */
  function eca_get_media_path($format, $size){
    global $formatFolder;
    $path = MEDIA_PATH;
    if( $formatFolder[$format] != "")
      $path .= $formatFolder[$format] . '/';
    else
      $path .= 'formatUnkown' . '/';
      
    if( !empty($size) && $size != '' && $format != 'pdf' )
      $path .= $size . '/';
    else
       $path .= '/';
       
    return $path;
  }
  
  /*
   * prints a markup-snippet, with a list of artists
   */
  function print_agents($agents){
    $output = 'Artist(s): ';
    foreach($agents as $agent){
      $output .= l($agent->title, 'node/' . $agent->nid, array( 'attributes' => array('title' => $agent->title)) ) . ' ';
    }
    print $output;
  }
  
  function print_awards($awards){
    $output = 'Awards(s): ';
    foreach($awards as $award){
      $output .= l($award->title, 'award/' . $award->award_id, array( 'attributes' => array('title' => $award->title, 'class' => 'dialog-link')) ) . ' ';
    }
    print $output;
  }
  
  function return_artworks( $artworks ){
    foreach($artworks as $artwork){
      if($output != '')
        $output .= ', ';
      
      $output .= l($artwork->title, 'artwork/' . $artwork->artwork_id, array( 'attributes' => array('title' => $artwork->title)) );
    }
    return $output;  
  }
  
  function return_owners( $owners ){
    $owner_str = '';
    foreach( $owners['agents'] as $agent ){
      if($owner_str != '')
        $owner_str .= ', ';
      $owner_str .= l($agent->title, "node/$agent->nid", array('attributes' => array('title' => $agent->title)));
    }
    foreach( $owners['institutions'] as $institution ){
      if($owner_str != '')
        $owner_str .= ', ';
      $owner_str .= l($institution->name, "institution/$institution->institution_id", array('attributes' => array('title' => $institution->name, 'class' => 'dialog-link')));
    }
    return $owner_str;
  }
  
  function return_exhibitions( $exhibitions ){
    foreach($exhibitions as $exhibition){
      if($output != '')
        $output .= ', ';
      
      $output .= l($exhibition->name, 'exhibition/' . $exhibition->exhibition_id, array( 'attributes' => array('title' => $exhibition->name)) );
    }
    return $output;  
  }
  
  function return_collections( $items ){
    foreach($items as $item){
      if($output != '')
        $output .= ', ';
      
      $output .= l(_filter_url_trim($item->name, URL_LENGTH), 'collection/' . $item->collection_id, array( 'attributes' => array('title' => $item->name, 'class' => 'dialog-link')) );
    }
    return $output;  
  }
  
  function return_agents( $items ){
    foreach($items as $item){
      if($output != '')
        $output .= ', ';
      
      $output .= l(_filter_url_trim($item->first_name . ' ' . $item->last_name, URL_LENGTH), 'agent/' . $item->agent_id, array( 'attributes' => array('title' => $item->first_name . ' ' . $item->last_name )) );
      
      if($item->at_date != '')
        $output .= " (in $item->at_date)";
      if($item->as_editor)
        $output .= " (Ed.)";
    }
    return $output;  
  }
  
  function return_nodes( $items ){
    foreach($items as $item){
      if($output != '')
        $output .= ', ';
      
      $output .= l(_filter_url_trim($item->title, URL_LENGTH), 'node/' . $item->nid, array( 'attributes' => array('title' => $item->title )) );
      
    }
    return $output;  
  }
  
  function return_publications ( $items ){
    foreach($items as $item){
      if($output != '')
        $output .= ', ';
      
      $output .= l(_filter_url_trim($item->title, URL_LENGTH), 'publication/' . $item->publication_id, array( 'attributes' => array('title' => $item->title, 'class' => 'dialog-link')) );
    }
    return $output;  
  }
  
  function return_happenings( $items ){
    foreach($items as $item){
      if($output != '')
        $output .= ', ';
      
      $output .= l($item->name, 'exhibition/' . $item->exhibition_id, array( 'attributes' => array('title' => $item->name)) );
      if($item->from_date != '')
        $output .= " ($item->from_date until $item->to_date)";
    }
    return $output;  
  }
  
  function return_institutions( $items ){
    foreach($items as $item){
      if($output != '')
        $output .= ', ';
      
      $output .= l($item->name, 'institution/' . $item->institution_id, array( 'attributes' => array('title' => $item->name, 'class' => 'dialog-link')) );
      if($item->from_date != '')
        $output .= " ($item->from_date until $item->to_date)";
    }
    return $output;  
  }
  
  function return_organizers( $items ){
    $output = 'People: ' . return_nodes( $items['agent'] ) . '. Institutions: ' . return_institutions( $items['institution'] );
    return $output;
  }
  
  /*
   * prints a markup-snipped with a value-label couple
   */
  function print_value($value, $label){
   if(!empty($value) ) { 
     if(strcasecmp($label, "description") == 0)
       $value = _textile_process( array(1 =>$value) ); 
   ?>
     <div><span class="label"><?php print $label; ?>: &nbsp;</span><span class="value"> <?php print $value; ?></span></div>
   <?php } 
  }
  function return_value($value, $label){
   if(!empty($value) ) {
     if(strcasecmp($label, "description") == 0)
       $value = _textile_process( array(1 =>$value) );
       
     $output .= "<div><span class=\"label\">$label: &nbsp;</span><span class=\"value\">$value</span></div>";
    }
    return $output; 
  }

  function _eca_get_publication_title($id){
    $res = db_query("SELECT title FROM compartdb.publication WHERE publication_id = $id");
    
    $pub = db_fetch_object($res);
    
    return $pub->title;
  }