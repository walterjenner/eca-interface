<?php
//provide the path to the eca_main module for further needs
$eca_main_path = drupal_get_path('module', 'eca_main');

//include the file with the helper functions
require_once $eca_main_path . '/includes.inc';

  if(count($node->media)){
    if( eca_is_image( $node->media[0] ) || eca_is_video( $node->media[0] ) ){
      $showOnInfoPage = true; //if pic or video
    }
    else {
      $showOnInfoPage = false;
      $showMediaTab = true; //TODO is a weng schiach!
    }
  }
  


//IF TEASER
if($teaser){ 
?>

  <div class="node-teaser clear-both">
    <h2><?php print l(check_plain($node->title), 'node/' . $node->nid, array('attributes'=> array('title' => check_plain($node->title))) ); ?></h2>
  </div>

<?php 
//IF FULL NODE VIEW
} else { 
  
  //trim title
  //$title = _filter_url_trim($node->title, TITLE_LENGTH);


?>

  <div class="artwork-node">
    <div id="tabs" class="ui-tabs">      
      <h1 class="node-title artwork"><?php print check_plain($node->title); ?></h1>
      <?php print flag_create_link('bookmarks', $node->nid);  ?>
      <ul class="ui-tabs-nav">
          <li><a href="#info-tab" title="View basic infos about this artwork." rel="address:/"><span><?php print t('Summary'); ?></span></a></li>
          <?php if ($content_bottom): ?> 
            <li><a href="#related-tab" title="View related items of this artwork." rel="address:/related-tab"><span><?php print t('Related'); ?></span></a></li>
          <?php endif; ?>
          <?php if(count($node->media)>1 || $showMediaTab): ?>
            <li><a href="#media-tab" title="View pictures of this artwork." rel="address:/media-tab"><span><?php print t('Media'); ?> (<?php print count($node->media); ?>)</span></a></li>
          <?php endif; ?>
          <li><a href="#comment-tab" title="View comments on this person." rel="address:/comment-tab"><span><?php print t('Comments'); ?> (<?php print $comment_count; ?>)</span></a></li>
      </ul>
         
      
      <div id="info-tab" class="ui-tabs-panel">
        <?php
          
          if(count($node->media)){
            if( $showOnInfoPage ){
              $mediaMarkup = eca_get_media_markup($node->media[0], "medium");
              print "<div class=\"artwork-image\">$mediaMarkup</div>\n";
            }            
          }
                   
          print_value(return_nodes($node->artists), t('Artist(s)') );
          
          print_value($node->description, t('Description'), true);
          print_value($node->creation_year . return_location( $node->ca_l_city, $node->ca_l_country), t('Created'), false, '', false );
          print_value($node->ca_at_name, t('Artwork Type') );
          print_value($node->material, t('Material') );
          print_value($node->rights, t('Rights') );
          
          if($node->algorithm_id != 0 && $node->algorithm_id != ''){
            print_value(l($node->ca_al_name, 
                            "algorithm/$node->algorithm_id", 
                            array('attributes' => 
                              array('class' => 'dialog-link', 'title' => $node->ca_al_name )
                            )
                           ),
                        t('Algorithm')  
             );
          }          
         
          print_value(return_agents_by_node( $node->owners['agents'] ) . ' ' . return_institutions( $node->owners['institutions'] ), t('Owner(s)') );
          print_value( return_publications($node->citations), t('Cited in') );          
          print_value(return_collections( $node->collections ), t('Part of Collection') );   
          
         //print_value($node->algorithm_id, "Algorithm ID");  
        ?>
        
      </div>  
      
      <?php if($content_bottom): ?>
        <div id="related-tab">
            <?php print $content_bottom; ?>    
        </div>
      <?php endif; ?>
      
      <?php if( count($node->media)>1 || $showMediaTab): ?>     
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
      
      <div class="node-submitted">
        <?php 
          print t('Last change by !name on @last_change', 
                    array('!name' => $name,'@last_change' => format_date($node->last_change, 'small') ) ); 
        ?>
      </div>
      
    </div>
  </div>
    
<?php } //endif !$teaser 
