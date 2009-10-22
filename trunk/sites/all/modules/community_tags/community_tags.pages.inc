<?php
// $Id: community_tags.pages.inc,v 1.1.2.1 2008/07/19 20:10:18 herc Exp $

/**
 * @file
 * community_tags.pages.inc
 *
 * Page handlers of Community Tags.
 *
 * @defgroup community_tags_pages Community Tags page handlers.
 * @{
 */

/**
 * Quick tag form.
 */
function community_tags_form($form_state, $edit, $title = NULL) {
  $form['cloud'] = array(
    '#type' => 'markup',
    '#title' => t('All tags'),
    '#value' => $edit['cloud'],
  );
  
  $access = user_access('tag content');

  $form['tags'] = array(
    '#type' => 'textfield',
    '#title' => t('My tags'),
    '#maxlength' => 100,
    '#default_value' => $edit['tags'],
    '#required' => FALSE,
    '#autocomplete_path' => 'taxonomy/autocomplete/'. $edit['vid'],
    '#attributes' => array('class' => 'form-tags'),
    '#access' => $access,
  );
  if ($edit['inline']) {
    $form['tags']['#size'] = 20;
  }
  
  if (!$access) {
    $destination = drupal_get_destination();
    $form['login'] = array(
      '#type' => 'markup',
      '#value' => '<div>'. t('<a href="@login">Login</a> or <a href="@register">register</a> to tag items', array('@login' => url('user/login', array('query' => $destination) ), '@register' => url('user/register', array('query' => $destination)))) .'</div>',
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#access' => $access,
  );
  
  $form['node'] = array(
    '#type' => 'value',
    '#value' => $edit['node'],
  );
  
  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $edit['nid'],
  );

  $form['vid'] = array(
    '#type' => 'value',
    '#value' => $edit['vid'],
  );

  return $form;
}

/**
 * Validate the quick tag form.
 */
function community_tags_form_validate($form, &$form_state) {
  if ($form_state['values']['tags'] == '') {
    form_set_error('tags', t('You must enter at least one tag.'));
  }
}

/**
 * Submit callback for quick tag form.
 */
function community_tags_form_submit($form, &$form_state) {
  global $user;
  community_tags_taxonomy_node_save($form_state['values']['node'], array('tags' => array($form_state['values']['vid'] => $form_state['values']['tags'])), FALSE, $user->uid);

  $form_state['redirect'] = 'node/'. $form_state['values']['nid']; 
}

/**
 * Theme the quick tag form.
 * @ingroup themeable
 */
function theme_community_tags_form($form) {
  $output = theme('form_element', array('#title' => t('All tags')), drupal_render($form['cloud']));

  $output .= drupal_render($form);

  // We add the JS file this late, to ensure it comes after autocomplete.js.
  drupal_add_css(drupal_get_path('module', 'community_tags') .'/community_tags.css', 'module');
  drupal_add_js(drupal_get_path('module', 'community_tags') .'/community_tags.js');

  return $output;
}

/**
 * Menu callback: 
 */
function community_tags_mypage($uid = NULL) {
  $uid = isset($uid) ? $uid : $GLOBALS['uid'];

  _community_tags_get_tag_result('user', 100, $uid);
}

/**
 * Form builder; Builds the settings form.
 *
 * @ingroup forms
 */
function community_tags_settings() {
  $form = array();

  community_tags_rehash();

  // Build list of available free-tagging vocabularies
  $options = array();
  $vocabs = db_query('SELECT v.vid, v.name FROM {vocabulary} v WHERE v.tags = 1 ORDER BY v.weight, v.name');
  while ($vocabulary = db_fetch_object($vocabs)) {
    $options[$vocabulary->vid] = $vocabulary->name;
  }
  if ($options) {
    $form['community_tags_vocabularies'] = array(
      '#type' => 'select',
      '#multiple' => TRUE,
      '#title' => t('Community vocabularies'),
      '#default_value' => variable_get('community_tags_vocabularies', array()),
      '#options' => $options,
      '#description' => t('Which vocabularies should community tagging use? Note: only one community tagged vocabulary per node type is supported.'),
    );
  }

  $form = system_settings_form($form);

  return $form;
}

// Patch for Drupal 5.x. Remove for 6.x.
if (!function_exists('taxonomy_explode_tags')) {

  /**
   * Explode a string of given tags into an array.
   */
  function taxonomy_explode_tags($tags) {
    // This regexp allows the following types of user input:
    // this, "somecompany, llc", "and ""this"" w,o.rks", foo bar
    $regexp = '%(?:^|,\ *)("(?>[^"]*)(?>""[^"]* )*"|(?: [^",]*))%x';
    preg_match_all($regexp, $tags, $matches);
    $typed_tags = array_unique($matches[1]);

    $tags = array();
    foreach ($typed_tags as $tag) {
      // If a user has escaped a term (to demonstrate that it is a group,
      // or includes a comma or quote character), we remove the escape
      // formatting so to save the term into the database as the user intends.
      $tag = trim(str_replace('""', '"', preg_replace('/^"(.*)"$/', '\1', $tag)));
      if ($tag != "") {
        $tags[] = $tag;
      }
    }

    return $tags;
  }
}
