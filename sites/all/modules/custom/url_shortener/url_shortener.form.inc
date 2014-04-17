<?php

function url_shortener_page() {
  return drupal_get_form('url_shortener_form');
}

/**
 * Display Url shortener form
 *
 * @see url_shortener_form_validate().
 * @see url_shortener_form_submit().
 */
function url_shortener_form($form, &$form_state) {
  drupal_add_css(drupal_get_path('module', 'url_shortener') . '/styles/url_style.css');

  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter Url'),
    '#required' => TRUE,
  );

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

function url_shortener_form_validate(&$form, &$form_state) {
  //TODO: validate url
}

function url_shortener_form_submit($form, &$form_state) {
  global $base_url, $user;

  $url = $form_state['values']['url'];

  $res = db_query(
    'SELECT short_url FROM {urls} WHERE url=:url AND uid=:uid LIMIT 1',
    array(
      ':url' => $url,
      ':uid' => $user->uid,
    )
  )
  ->fetchField();

  if(!$res) {
    $res = _url_shortener_generate();
    db_insert('urls')
      ->fields(
        array(
          'url' => $url,
          'short_url' => $res,
          'created' => time(),
          'uid' => $user->uid,
          'count' => 0,
          'last_used' => 0,
          'active' => 1
        )
      )
      ->execute();
  }

  $link = $base_url . '/' . $res;
  drupal_set_message(t('Your url: ') . l($link, $link, array('attributes' => array('target' => '_blank') ) ) );
}

function _url_shortener_generate() {
  $short_url = base_convert(rand(10000, 99999), 10, 36);

  $res = db_query(
    'SELECT id FROM {urls} WHERE short_url=:short_url LIMIT 1',
    array(
      ':short_url' => $short_url,
    )
  )
  ->fetchField();

  if($res) {
    return _url_shortener_generate();
  }

  return $short_url;
}