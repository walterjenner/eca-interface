<?php
//provide the path to the eca_main module for further needs
$eca_main_path = drupal_get_path('module', 'eca_main');

//include the file with the helper functions
require_once $eca_main_path . '/includes.inc';

//IF TEASER
if($teaser){ 
?>

  <div class="node-teaser clear-both">
   <div class="teaser-thumb">
     <?php 
       if(count($node->media)>0){
         $mediaMarkup = eca_get_media_markup($node->media[0], 'thumbs');
         print $mediaMarkup;
       } else {
         print  "<img scr=\"$eca_main_path/img/agent_dummy.png\" alt=\"agent_dummy\" />";
       }
     ?>
   </div>
   <h2><?php print l(check_plain($node->title), 'node/' . $node->nid, array('attributes'=> array('title' => check_plain($node->title))) ); ?></h2>
  </div>

<?php 
//IF FULL NODE VIEW
} else { 
  
  //trim title
  $title = _filter_url_trim($node->title, URL_LENGTH);


?>

  <div class="artwork-node">
    <div id="tabs">      
      <h2 class="node-title"><?php print check_plain($title); ?></h2>
      <?php print flag_create_link('bookmarks', $node->nid);  ?>
      <ul>
          <li><a href="#info-tab" title="View basic infos about this artwork." rel="address:/"><span>Info</span></a></li>
          <?php if(count($node->media)): ?>
            <li><a href="#media-tab" title="View pictures of this artwork." rel="address:/media-tab"><span>Media (<?php print count($node->media); ?>)</span></a></li>
          <?php endif; ?>
          <li><a href="#comment-tab" title="View comments on this person." rel="address:/comment-tab"><span>Comments (<?php print $comment_count; ?>)</span></a></li>
      </ul>
         
      <div class="hr-grey"></div>
      <div id="info-tab" class="ui-tabs-panel">
        <?php
          
          if(count($node->media)){
            $mediaMarkup = eca_get_media_markup($node->media[0], "medium");
            print "<div class=\"artwork-image\">$mediaMarkup</div>\n";
          }
          print("<p>Content Author: $name</p>");
          print_agents($node->artists);
          
          print_value($node->title, "Full title");
          print_value($node->ca_at_name, 'Artwork Type' );
          print_value(_textile_process(array(1 => $node->description)), "Description");
          print_value($node->creation_year, "Year of creation");
          print_value($node->material, "Material");
          print_value($node->rights, "Rights");
          
          if($node->algorithm_id != 0 && $node->algorithm_id != ''){
            print_value(l($node->ca_al_name, 
                            "algorithm/$node->algorithm_id", 
                            array('attributes' => 
                              array('class' => 'dialog-link', 'title' => $node->ca_al_name )
                            )
                           ),
                        'Algorithm'  
             );
          }
          
          //LOCATION 
          if($node->creation_location_id != 0 && $node->creation_location_id != ''){
            print '<h4>Created in</h4>';
            //print_value($node->creation_location_id, "creation_location_id");
            print_value("$node->ca_l_city, $node->ca_l_country", "Location");
            print_value($node->ca_l_description, "Description");
          }
          
          //OWNERS
          $owner_str = '';
          foreach( $node->owners['agents'] as $agent ){
            if($owner_str != '')
              $owner_str .= ', ';
            $owner_str .= l($agent->title, "node/$agent->nid", array('attributes' => array('title' => $agent->title)));
          }
          foreach( $node->owners['institutions'] as $institution ){
            if($owner_str != '')
              $owner_str .= ', ';
            $owner_str .= l($institution->name, "institution/$institution->institution_id", array('attributes' => array('title' => $institution->name, 'class' => 'dialog-link')));
          }
          print_value($owner_str, 'Owner(s)');          
          
          //CITATIONS
          $citation_str = return_publications($node->citations);
          print_value($citation_str, 'Cited in');          
          
          //COLLECTIONS
          $collection_str = return_collections( $node->collections );
          print_value($collection_str, 'Part of Collection');   
          
          //print_value($node->algorithm_id, "Algorithm ID");  
        ?>
        <h3>Assigned Tags</h3> 
          <?php print $node->content['community_tags']['#value']; ?>
      </div>  
      
      <?php if(count($node->media)): ?>     
        <div id="media-tab" class="ui-tabs-panel">
          <?php 
            foreach($node->media as $media){
              $mediaMarkup = eca_get_media_markup($media, "medium");
              print "<div>$mediaMarkup</div>\n";
            }      
          ?>
        </div>
      <?php endif; ?>
      <div id="comment-tab" class="ui-tabs-panel">
        <?php 
            print $comments;
            
            if(empty($comments))
              print $links;      
          ?>
          <div class="clear-both">&nbsp;</div> 
      </div>
    </div>
  </div>
    
<?php } //endif !$teaser 
