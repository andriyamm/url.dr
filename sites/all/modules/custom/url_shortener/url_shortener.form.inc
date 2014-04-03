<?php

function url_shortener_page() {
  return drupal_get_form('url_shortener_form');
}

function url_shortener_form($form, &$form_state) {

  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => t('EUrl'),
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

  $url = $form_state['values']['url'];

  $res = db_query(
    'SELECT short_url FROM {urls} WHERE url=:url LIMIT 1',
    array(
      ':url' => $url,
    )
  )
  ->fetchField();

  if($res) {
    drupal_set_message(t('Your url: @short_url', array('@short_url' => $res)));
    //return $res;
  }
  else {
    $short_url = _url_shortener_generate();
    db_insert('urls')
      ->fields(
        array(
          'url' => $url,
          'short_url' => $short_url,
        )
      )
      ->execute();
    drupal_set_message(t('Your url: @short_url', array('@short_url' => $short_url)));
    //return $short_url;
  }

}

function _url_shortener_generate() {
  $short_url = base_convert(rand(10000,99999), 10, 36);

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