<?php
//provide the path to the eca_main module for further needs
db_set_active('default');
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
  if(strlen($node->title) > 40 + 3 )
    $title = substr(check_plain($node->title), 0, 43) . '...';
  else
    $title = $node->title;


?>

  <div class="exhibition-node">
    <div id="tabs">
      <h2 class="node-title"><?php print check_plain($title); ?></h2>
      <?php print flag_create_link('bookmarks', $node->nid);  ?>   
      <ul>
          <li><a href="#info-tab" title="View basic infos about this exhibition." rel="address:/"><span>Info</span></a></li>
          <?php if(count($node->media)): ?>
            <li><a href="#media-tab" title="View pictures of this exhibition." rel="address:/media-tab"><span>Media (<?php print count($node->media); ?>)</span></a></li>
          <?php endif; ?>
          <li><a href="#comment-tab" title="View comments on this exhibition." rel="address:/comment-tab"><span>Comments (<?php print $comment_count; ?>)</span></a></li>
      </ul>
       
      <div class="hr-grey"></div>
      <div id="info-tab" class="ui-tabs-panel">
        <?php
                  
          if(count($node->media)){
            if( eca_is_image( $node->media[0] ) ){
              $mediaMarkup = eca_get_media_markup($node->media[0], "medium");
              print "<div class=\"artwork-image\">$mediaMarkup</div>\n";
            }  
          }          
           print("<p>Content Author: $name</p>");
          print_value($node->title, "Full title"); 
          print_value( _textile_process(array(1 =>$node->description)), "Description");
          
          print_value( return_institutions($node->institutions), 'Shown at');
          print_value( return_publications($node->citations), 'Cited in');
           print_value( return_organizers($node->organizers), 'Organizer(s)');
          
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
