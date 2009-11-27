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
  $title = _filter_url_trim($node->title, TITLE_LENGTH);


?>

  <div class="artwork-node">
    <div id="tabs">      
      <h1 class="node-title"><?php print check_plain($title); ?></h1>
      <?php print flag_create_link('bookmarks', $node->nid);  ?>
      <ul>
          <li><a href="#info-tab" title="View basic infos about this artwork." rel="address:/"><span>Info</span></a></li>
          <?php if ($content_bottom): ?> 
            <li><a href="#related-tab" title="View related items of this artwork." rel="address:/related-tab"><span>Related Items</span></a></li>
          <?php endif; ?>
          <?php if(count($node->media)>1): ?>
            <li><a href="#media-tab" title="View pictures of this artwork." rel="address:/media-tab"><span>Media (<?php print count($node->media); ?>)</span></a></li>
          <?php endif; ?>
          <li><a href="#comment-tab" title="View comments on this person." rel="address:/comment-tab"><span>Comments (<?php print $comment_count; ?>)</span></a></li>
      </ul>
         
      
      <div id="info-tab" class="ui-tabs-panel">
        <?php
          
          if(count($node->media)){
            $mediaMarkup = eca_get_media_markup($node->media[0], "medium");
            print "<div class=\"artwork-image\">$mediaMarkup</div>\n";
          }
                   
          if(strlen($title) < strlen($node->title) )
            print_value($node->title, "Full title");
          
          print_value(return_agents_by_node($node->artists), 'Artist(s)');
          
          print_value(_textile_process(array(1 => $node->description)), "Description", true);
          print_value($node->creation_year . return_location( $node->ca_l_city, $node->ca_l_country), 'Created');
          print_value($node->ca_at_name, 'Artwork Type' );
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
         
          print_value(return_agents_by_node( $node->owners['agents'] ) . ' ' . return_institutions( $node->owners['institutions'] ), 'Owner(s)');
          print_value( return_publications($node->citations), 'Cited in' );          
          print_value(return_collections( $node->collections ), 'Part of Collection');   
          
         //print_value($node->algorithm_id, "Algorithm ID");  
        ?>
        
      </div>  
      
      <?php if($content_bottom): ?>
        <div id="related-tab">
            <?php print $content_bottom; ?>    
        </div>
      <?php endif; ?>
      
      <?php if(count($node->media)>1): ?>     
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
      
      <div class="node-submitted">Last change by <?php print($name); ?> on <?php print(format_date($node->last_change, 'small')); ?></div>
      
    </div>
  </div>
    
<?php } //endif !$teaser 