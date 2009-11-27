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
      <h1 class="node-title"><?php print /*$node->academic_title . ' ' . */check_plain($node->title); ?></h1>
      
      <?php print flag_create_link('bookmarks', $node->nid);  ?>
            
      <ul>
          <li><a href="#info-tab" title="View basic infos about this person." rel="address:/"><span>Info</span></a></li>
          <?php if($node->biography!=''): ?>
            <li><a href="#biography-tab" title="View biography of this person." rel="address:/biography-tab"><span>Biography</span></a></li>
          <?php endif; ?>
          <?php if ($content_bottom): ?> 
            <li><a href="#related-tab" title="View related items of this person." rel="address:/related-tab"><span>Related Items</span></a></li>
          <?php endif; ?>
          <?php if(count($node->media)): ?>
            <li><a href="#media-tab" title="View pictures of this person." rel="address:/media-tab"><span>Media (<?php print count($node->media); ?>)</span></a></li>
          <?php endif; ?>
          <li><a href="#comment-tab" title="View comments on this person." rel="address:/comment-tab"><span>Comments (<?php print $comment_count; ?>)</span></a></li>
      </ul>
                
      
      <div id="info-tab" class="ui-tabs-panel">
        <?php
          if(count($node->media)){
            $mediaMarkup = eca_get_media_markup($node->media[0], "medium");
            print "<div class=\"agent-image\">$mediaMarkup</div>\n";
          }
          
          print_value($node->birth_date . return_location( $node->ca_l_city, $node->ca_l_country ), "Born");
          print_value($node->death_date . return_location( $node->ca_dl_city, $node->ca_dl_country ), "Died");
          print_value($node->pseudonym, "Pseudonymous");
          print_value( _textile_process(array(1 =>$node->description)), "Description", true);
          //print_value($node->email, "Email (NOTE: remove?)");
          if($node->url)
            print_value( l($node->url, 'http://'.$node->url ), 'Webpage');  
          print_value( return_awards($node->awards), 'Award(s)');
          print_value( return_institutions($node->institutions), 'Member of institution(s)' );  
          print_value( return_publications($node->citations), 'Cited in');
          print_value( return_collectives($node->collectives), 'Part of collective(s)');
          print_value( return_exhibitions($node->exhibitions), 'Exhibitions organized');              
        ?>
        
              
                 
      </div>  
      
      <?php if($node->biography!=''): ?>
        <div id="biography-tab" class="ui-tabs-panel">
          <?php print _textile_process(array(1 =>$node->biography)); ?>
        </div>
      <?php endif; ?>
      
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
      
      <div class="node-submitted">Last change by <?php print($name); ?> on <?php print(format_date($node->last_change, 'small')); ?></div>  
          
    </div>
  </div>
    
<?php } //endif !$teaser 
