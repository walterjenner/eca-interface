<?php
// $Id: search-results.tpl.php,v 1.1 2007/10/31 18:06:38 dries Exp $

/**
 * @file search-results.tpl.php
 * Default theme implementation for displaying search results.
 *
 * This template collects each invocation of theme_search_result(). This and
 * the child template are dependant to one another sharing the markup for
 * definition lists.
 *
 * Note that modules may implement their own search type and theme function
 * completely bypassing this template.
 *
 * Available variables:
 * - $search_results: All results as it is rendered through
 *   search-result.tpl.php
 * - $type: The type of search, e.g., "node" or "user".
 *
 *
 * @see template_preprocess_search_results()
 * 
 * 
 *
 * NOTE: if this template is in use, the finder search fallback does not work anymore. strange..  
 * 
 */
?>

<div class="search-form-info">
  <div class="hints">Hints:</div>
  <ul>
    <li>You can wrap multiple words with double quotation marks in order search for that exact phrase.</li>
    <li>You can use AND/OR to refine your search</li>
    <li>You can use the minus symbol (-) to exclude words-</li>
  </ul>
</div>

<dl class="search-results <?php print $type; ?>-results">
  <?php print $search_results;?>
</dl>
<?php print $pager; ?>