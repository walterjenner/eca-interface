<?php
// $Id$

//see page.tpl.readme

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">

<head>
  <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
  <meta name="google-site-verification" content="BLANGnrDbAcQ5m8le1tcIJP3L8Z6ExCUERyJsyZjXx8" />
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
  
</head>
<body class="<?php print $body_classes; ?>">

  <div id="page"><div id="page-inner">

    <a name="top" id="navigation-top"></a>
    <?php if ($primary_links || $secondary_links || $navbar): ?>
      <div id="skip-to-nav"><a href="#navigation"><?php print t('Skip to Navigation'); ?></a></div>
    <?php endif; ?>
    
    <div id="header"><div id="header-inner" class="clear-block">

      <?php if ($logo || $site_name || $site_slogan): ?>
        <div id="logo-title">

          
          <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home"><span id="logo"></span></a>
          

          <?php if ($site_name): ?>
            <div id="site-name"><strong>
              <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
              <?php print $site_name; ?>
              </a>
            </strong></div>
          <?php endif; ?>

          <?php if ($site_slogan): ?>
            <div id="site-slogan"><?php print $site_slogan; ?></div>
          <?php endif; ?>

        </div> <!-- /#logo-title -->
      <?php endif; ?>
        
      <?php if ($search_box || $primary_links || $navbar): ?>
        <div id="navbar"><div id="navbar-inner" class="clear-block region region-navbar">

          <a name="navigation" id="navigation"></a>

          <?php if ($primary_links): ?>
            <div id="primary">
              <?php print theme('links', $primary_links); ?>
            </div> <!-- /#primary -->
            
          <?php endif; ?>
          
          
          <div id="finder-box">
            <?php /*print $search_box;*/ ?>
            <?php 
               //drupal_add_js(drupal_get_path('module', finder_autocomplete) .'/finder_autocomplete.js');
              print finder_view(finder_load(1), 'block'); 
            ?>
          </div> <!-- /#search-box -->
          
          
          <?php if ($secondary_links): ?>
            <div id="secondary">
              <?php print theme('links', $secondary_links); ?>
            </div> <!-- /#secondary -->
          <?php endif; ?>
          
          

          <?php print $navbar; ?>

        </div></div> <!-- /#navbar-inner, /#navbar -->
      <?php endif; ?>
       
      <?php if ($header): ?>
        <div id="header-blocks" class="region region-header">
          <?php print $header; ?>
        </div> <!-- /#header-blocks -->
      <?php endif; ?>

    </div></div> <!-- /#header-inner, /#header -->
        
    <div id="main"><div id="main-inner" class="clear-block<?php if ($search_box || $primary_links || $secondary_links || $navbar) { print ' with-navbar'; } ?>">
      
    <div id="content">
          
      <div id="content-inner" style="clear:both;">
        

        <?php if ($mission): ?>
          <div id="mission"><?php print $mission; ?></div>
        <?php endif; ?>

        <?php if ($content_top): ?>
          <div id="content-top" class="region region-content_top">
            <?php print $content_top; ?>
          </div> <!-- /#content-top -->
        <?php endif; ?>

        <?php if ($breadcrumb || $title || $tabs || $help || $messages): ?>
          <div id="content-header">
            <?php print $breadcrumb; ?>
            <?php if ($title && $node->type != 'agent'      && $node->type != 'artwork' 
                             && $node->type != 'exhibition' && $node->type != 'publication' 
                             && $node->type != 'institution'): 
            ?>
              <h1 class="title"><?php print $title; ?></h1>
            <?php endif; ?>
            <?php print $messages; ?>
            <?php if ($tabs): ?>
              <div class="tabs"><?php print $tabs; ?></div>
            <?php endif; ?>
            <?php print $help; ?>
          </div> <!-- /#content-header -->
        <?php endif; ?>

        <div id="content-area">
          <?php print $content; ?>          
                   
          <?php 
          // if there is content _bottom, and the node type none of the listed, print. 
          //(in the listed node-type $content_bottom is output in the node.tpl.php)
          if( $content_bottom && !(strpos($body_classes, 'node-type-agent') 
                    || strpos($body_classes, 'node-type-exhibition')
                    || strpos($body_classes, 'node-type-publication')
                    || strpos($body_classes, 'node-type-institution')   
                    || strpos($body_classes, 'node-type-artwork')) ): ?>    
            
            <div id="content-bottom" class="region region-content_bottom">
              <?php print $content_bottom; ?>
            </div> <!-- /#content-bottom -->            
          <?php endif; ?> 
          
         <div class="clear-both"></div>
        
        </div>
        
        <?php if ($feed_icons): ?>
          <div class="feed-icons"><?php print $feed_icons; ?></div>
        <?php endif; ?>

      </div></div> <!-- /#content-inner, /#content -->

      <?php if ($left): ?>
        <div id="sidebar-left"><div id="sidebar-left-inner" class="region region-left">
          <?php print $left; ?>
        </div></div> <!-- /#sidebar-left-inner, /#sidebar-left -->
      <?php endif; ?>

      <?php if ($right): ?>
        <div id="sidebar-right"><div id="sidebar-right-inner" class="region region-right">
          <?php print $right; ?>
        </div></div> <!-- /#sidebar-right-inner, /#sidebar-right -->
      <?php endif; ?>

    </div></div> <!-- /#main-inner, /#main -->

    <?php if ($footer || $footer_message): ?>
      <div id="footer"><div id="footer-inner" class="region region-footer">

        <?php if ($footer_message): ?>
          <!-- <div id="footer-message"><?php print $footer_message; ?></div> -->
        <?php endif; ?>

        <?php print $footer; ?>

      </div></div> <!-- /#footer-inner, /#footer -->
    <?php endif; ?>

  </div></div> <!-- /#page-inner, /#page -->
  <div id="page-bottom">
    <?php if ($closure_region): ?>
      <div id="closure-blocks" class="region region-closure"><?php print $closure_region; ?></div>
    <?php endif; ?>
  
    <?php print $closure; ?>
  </div><!-- /#page-bottom -->

</body>
</html>
