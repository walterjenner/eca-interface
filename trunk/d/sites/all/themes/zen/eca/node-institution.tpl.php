<?php
//provide the path to the eca_main module for further needs
$eca_main_path = drupal_get_path('module', 'eca_main');

//include the file with the helper functions
require_once $eca_main_path . '/includes.inc';

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

  <div class="publication-node">
    <div id="tabs" class="ui-tabs">
      <h1 class="node-title publication"><?php print check_plain($node->title); ?></h1>
      
        <?php print flag_create_link('bookmarks', $node->nid);  ?>   
        <ul class="ui-tabs-nav">
            <li><a href="#info-tab" title="View basic infos about this publication." rel="address:/"><span><?php print t('Summary'); ?></span></a></li>
            <?php if($content_bottom): ?>
              <li><a href="#related-tab" title="View related items of this publication." rel="address:/related-tab"><span><?php print t('Related'); ?></span></a></li>
            <?php endif; ?>
            <?php if(count($node->media)): ?>
              <li><a href="#media-tab" title="View pictures of this publication." rel="address:/media-tab"><span><?php print t('Media'); ?> (<?php print count($node->media); ?>)</span></a></li>
            <?php endif; ?>
            <li><a href="#comment-tab" title="View comments on this publication." rel="address:/comment-tab"><span><?php print t('Comments'); ?> (<?php print $comment_count; ?>)</span></a></li>
        </ul>
      
       
     
      <div id="info-tab" class="ui-tabs-panel">
        <?php
                  
          if(count($node->media)){
            if( eca_is_image( $node->media[0] ) ){
              $mediaMarkup = eca_get_media_markup($node->media[0], "medium");
              print "<div class=\"agent-image\">$mediaMarkup</div>\n";
            }  
          }          
          
          if(is_empty($node->it_name))
            print('<h3>' . t('Institution') .'</h3>');
          else
            print('<h3>'.$node->it_name.'</h3>');
          
          print_value($node->description, t('Description') );
          if(!is_empty($item->url))
            print_value(l($node->url, absolute($item->url)), 'Web page');
          print_value(return_address($node->street, $node->zip, $node->city, $node->country), t('Address') );
          
          print_value( return_happenings( $node->happenings ), t('Happening(s)') );
          print_value( return_happenings( $node->exhibitions ), t('Exhibition(s) organized') );
          print_value( return_artworks( $node->artworks ), t('Artwork(s) owned') );
          print_value( return_collections( $node->collections ), t('Collection(s) owned') );
          print_value( return_publications( $node->citations ), t('Cited in') );
          
        ?>
        
      </div>  
      
      <?php if($content_bottom): ?>
        <div id="related-tab">
            <?php print $content_bottom; ?>    
        </div>
      <?php endif; ?>
      
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
      
      <div class="node-submitted">
        <?php 
          print t('Last change by !name on @last_change', 
                    array('!name' => $name,'@last_change' => format_date($node->last_change, 'small') ) ); 
        ?>
      </div>
      
    </div>
  </div>
    
<?php } //endif !$teaser 
