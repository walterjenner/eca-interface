<?php 
  //the path to all media files
  define("MEDIA_PATH", "http://localhost/www/eca/public/");
  //define("MEDIA_PATH", "http://localhost/www/eca/public/");
  define("URL_LENGTH", 45);
  define("TITLE_LENGTH", 30);
  define("RELATED_ITEM_LIMIT", 10); //how many items should be shown in the "related items" tab.
  define("TEXTILE_FORMAT_ID", 3); //the id of the input format (aka filter) of the Textile filter
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
                        1000016 => 5, //jörn
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
    
    $selectMedia = "SELECT mf.file_name, mf.format, mf.description FROM compartDB.illustrated_by LEFT JOIN compartDB.media_file mf ON illustrated_by.media_file_id = mf.media_file_id WHERE illustrated_by.row_id = $row_id AND illustrated_by.table_id = $table_id";
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
  function eca_get_media_markup($media, $size, $image_link = false){
    $path = eca_get_media_path($media->format, $size);
    if(!is_empty($size) && eca_is_image($media)) //note: seems like all thumbs and medium images are jpg's
      $path .= $media->file_name . '.' . jpg;
    else
      $path .= $media->file_name . '.' . $media->format;
    
    $output = '';
    if( eca_is_image($media) )
    {
      if( $image_link ){
        $output .= l($media->file_name, $path);
        return $output;
      }
      else {
        $output .= '<div>';
        $output .= "<img src=\"$path\" alt=\"$media->file_name\" />";
        $output .= "<br/>$media->description</div>";
        return $output; 
      }
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
      
    if( !is_empty($size) && $format != 'pdf' )
      $path .= $size . '/';
    //else
       //$path .= '/';
       
    return $path;
  }
  
  function DEP_print_awards($awards){
    $output = 'Award(s): ';
    foreach($awards as $award){
      $output .= l($award->title, 'award/' . $award->award_id, array( 'attributes' => array('title' => $award->description, 'class' => 'dialog-link')) ) . ' ';
    }
    print $output;
  }
  
  function return_media_links( $media ){    
    if(count($media)==0)
      return;
    
    $output = '';
    foreach($media as $mediafile ){
      if($output != '')
        $output .= ', ';
      $output .= eca_get_media_markup($mediafile,'medium',true); 
    }
    return $output;
  }
  
  function return_address($street, $zip, $city, $country, $pobox = '', $additional = ''){
    $output = '<div class="address"><br/>';
    $noAddress = true;
    if( !is_empty($street) ){
      $output .= $street . '<br/>';
      $noAddress = false;
    }
    if( !is_empty($additional) ){
      $output .= $additional . '<br/>';
      $noAddress = false;
    }
    if( !is_empty($pobox) ){
      $output .= $pobox . '<br/>';
      $noAddress = false;
    }
    if( !is_empty($zip) ){
      $output .= $zip;
      $noAddress = false;
    }
    if( !is_empty($city) ){
      if(!is_empty($zip))
        $output .= ' - ';
      $output .= $city;
      $noAddress = false;      
    }
    if( !is_empty($country) ){
        $output .= '<br/>' . $country; 
        $noAddress = false;
    }
    $output .= '</div>';
    
    if( $noAddress )
      return;
    else  
      return $output;
  }
  
  function return_location($city, $country){
    $output = '';
    if(!is_empty($city)){
      $output .= ' in ' . $city;
      if( is_empty($country) )
        $output .= '.';
    }
    if(!is_empty($country)){
      if($output != ''){
        $output .= ', ';
      }
      else {
        $output .= ' in ';
      }
      $output .= $country . '.';
    }
     return $output; 
  }
  
  function return_collectives($items){
    foreach($items as $item){
      $output .= l($item->name, 'collective/' . $item->collective_id, array( 'attributes' => array('title' => $item->description, 'class' => 'dialog-link')) ) . ' ';
    }
    return $output;
  }
  
  function return_awards($awards){
    foreach($awards as $award){
      $output .= l($award->title, 'award/' . $award->award_id, array( 'attributes' => array('title' => $award->title, 'class' => 'dialog-link')) ) . ' ';
    }
    return $output;
  }
  
  /*
   * params: title, creation_year, nid, file_name, format
   */
  function return_artwork_thumb( $node, $link = true ){
    $output .= '<li>';
    
    if(!is_empty($node->creation_year))
      $yearString = ' - Date: ' . $node->creation_year;
    
    if($link){
      $output .= l('<img src="'.MEDIA_PATH.'imageUploads/thumbs/'.$node->file_name.'.jpg" alt="'.$node->title.'" />', 
                    "node/$node->nid", 
                    array( 'html' => true, 'attributes' => array('title' => 'Title: ' . $node->title . $yearString, 'class' => 'artwork-tooltip' ) ));
    }else {
        $output .= '<img src="'.MEDIA_PATH.'imageUploads/thumbs/'.$node->file_name.'.jpg" alt="'.$node->title.'" class="current-item" />';
    }
    $output .= '</li>';
    return $output;
  }
  
  function return_artworks( $artworks ){
    foreach($artworks as $artwork){
      if($output != '')
        $output .= ', ';
      
      $output .= l($artwork->title, 'artwork/' . $artwork->artwork_id, array( 'attributes' => array('title' => $artwork->title)) );
    }
    return $output;  
  }
  
  function return_collection( $collection ){
    $output = '';
    $output .= '<span class="tag tag-artwork">'; 
    $output .= l(  _filter_url_trim($collection->name, URL_LENGTH), 
                  'collection/'.$collection->collection_id, 
                   array('attributes' => array('title' => $collection->name, 'class' => 'dialog-link')));
    $output .= '</span>';
    return $output;
  }
  
  function return_artwork( $node, $link = true ){
    $output = '';
    if($link)
      $output .= '<span class="tag tag-artwork">' . l( _filter_url_trim($node->title, URL_LENGTH) , 'node/'.$node->nid, array( 'attributes' => array('title' => $node->title) )) . '</span>';
    else
      $output .= '<span class="tag tag-artwork-active">' . _filter_url_trim($node->title, URL_LENGTH) . '</span>';
    return $output;
  }
  
  function return_owners( $owners ){
    $owner_str = '';
    if( is_array($owners['agents']) ){
      foreach( $owners['agents'] as $agent ){
        if($owner_str != '')
          $owner_str .= ', ';
        $owner_str .= l($agent->title, "node/$agent->nid", array('attributes' => array('title' => $agent->title)));
      }
    }
    if( is_array($owners['institutions']) ){
      foreach( $owners['institutions'] as $institution ){
        if($owner_str != '')
          $owner_str .= ', ';
        $owner_str .= l($institution->name, "institution/$institution->institution_id", array('attributes' => array('title' => $institution->name, 'class' => 'dialog-link')));
      }
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
  
  /*
   * returns a markup-snippet, with a list of artists
   */
  function return_agents_by_node($agents){
    $output = '';
    foreach($agents as $agent){
      if($output != '')
        $output .= ', ';
      $output .= l($agent->title, 'node/' . $agent->nid, array( 'attributes' => array('title' => $agent->title)) );
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
    $output = '';
    $people_str = return_nodes( $items['agent'] );
    $inst_str = return_institutions( $items['institution'] );
    if($people_str)
      $output .= $people_str . '. ';
    if( $inst_str ){
      if($output!=''){
        $output .= '(Institution: ' . $inst_str . ').';
      }
      else { 
        $output .= $inst_str . '.';
      }
    }    
    
    return $output;
  }
  
  /*
   * prints a markup-snipped with a value-label couple
   */
  function print_value($value, $label, $multiline = false, $class_str = '', $colon = true, $showLabel = true){
    print( return_value($value, $label, $multiline, $class_str, $colon, $showLabel) );
  }
  
  function return_value($value, $label, $multiline = false, $class_str = '', $colon = true, $showLabel = true){
    if(!is_empty($value) ) { 
     if(strcasecmp($label, "description") == 0){
       $value = check_markup( $value, TEXTILE_FORMAT_ID, false );
       //$multiline = true;
       $showLabel = false;
     }
     
     if($nolabel)
       $multiline = false;
   
     $output .= '<div class="label_value_pair">';
     if($showLabel){
       $output .= ($colon)?'<span class="label">':'<span>';
       $output .= $label;
       $output .= ($colon)?':':'';
       $output .= '&nbsp;</span>';
       $output .= ($multiline)?'<br/>':'';
     }
     $output .= '<span class="value ' . $class_str . '">' . $value .'</span></div>';
    }
    
    return $output; 
  }

  function get_publication_title($id){
    $res = db_query("SELECT title FROM compartDB.publication WHERE publication_id = $id");    
    $pub = db_fetch_object($res);    
    return $pub->title;
  }
  
  function is_empty($string) {
    return (strlen(trim($string)) == 0);	
  }
  
  function add_space( $string ){
    return ' ' . $string . ' ';
  }
  
  function implode2($glue="", $var){
    if ($var){
        foreach ($var as $value){
            $array[]=strval($value);
        }
        return implode($glue, $array);
    }
    else return false;
 } 
