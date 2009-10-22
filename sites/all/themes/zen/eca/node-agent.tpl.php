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
?>

  <div class="agent-node">
    <div id="tabs">
      <h2 class="node-title"><?php print /*$node->academic_title . ' ' . */check_plain($node->title); ?></h2>
      
      <?php print flag_create_link('bookmarks', $node->nid);  ?>
            
      <ul>
          <li><a href="#info-tab" title="View basic infos about this person." rel="address:/"><span>Info</span></a></li>
          <?php if($node->biography!=''): ?>
            <li><a href="#biography-tab" title="View biography of this person." rel="address:/biography-tab"><span>Biography</span></a></li>
          <?php endif; ?>
          <?php if(count($node->media)): ?>
            <li><a href="#media-tab" title="View pictures of this person." rel="address:/media-tab"><span>Media (<?php print count($node->media); ?>)</span></a></li>
          <?php endif; ?>
          <li><a href="#comment-tab" title="View comments on this person." rel="address:/comment-tab"><span>Comments (<?php print $comment_count; ?>)</span></a></li>
      </ul>
                
      <div class="hr-grey"></div>
      <div id="info-tab" class="ui-tabs-panel">
        <?php
          print("<p>Content Author: $name</p>");
          print_value($node->birth_date, "Birthday");
          print_value($node->death_date, "Died on");
          print_value($node->pseudonym, "Pseudonym");
          print_value( _textile_process(array(1 =>$node->description)), "Description");
          print_value($node->email, "Email (NOTE: remove?)");
          print_value( l($node->url, $node->url ), "Webpage");  
          print_awards($node->awards);
          print_value( return_institutions($node->institutions), "Member of institution(s)" );
        ?>
        <h3>Assigned Tags</h3> 
          <?php print $node->content['community_tags']['#value']; ?>
      </div>  
      
      <?php if($node->biography!=''): ?>
        <div id="biography-tab" class="ui-tabs-panel">
          <?php print _textile_process(array(1 =>$node->biography)); ?>
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
    </div>
  </div>
    
<?php } //endif !$teaser 
