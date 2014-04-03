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

function url_shortener_form_submit(&$form, &$form_state) {
//TODO submit
}
