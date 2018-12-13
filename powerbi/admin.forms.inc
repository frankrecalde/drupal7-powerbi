<?php

/**
 * @file
 * Contains administrative forms and their handlers.
 */

/**
 * Power BI settings form.
 */
function powerbi_settings_form($form_state, $form_id) {

  $pbi_url = 'https://powerbi.microsoft.com/en-us/landing/signin/';
  $form['settings'] = array(
    '#type' => 'vertical_tabs',
  );
  // Administer setting tab.
  $form['administer'] = array(
    '#type' => 'fieldset',
    '#title' => t('Administer settings'),
    '#group' => 'settings',
    '#description' => t('Information below will be used for authenticating an user credentials with power BI service in order to embedding PBI data with this site.'),
  );
  // Site wide setting tab.
  $form['site'] = array(
    '#type' => 'fieldset',
    '#title' => t('Site wide settings'),
    '#group' => 'settings',
    '#description' => t('This setting will be available for non administrative activities.'),
  );
  $form['administer']['pbi_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Power BI User Name'),
    '#description' => t('Enter your <a href="@power-bi">Power BI</a> master account user name, which will be used for getting auth token., example:john.doe@yourdomain.com.', array('@power-bi' => $pbi_url)),
    '#default_value' => variable_get('pbi_username',''),
    '#required' => TRUE,
  );
  $form['administer']['pbi_client_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Power BI Application ID'),
    '#description' => t('Enter your <a href="@power-bi">Power BI</a> registered application ID.', array('@power-bi' => $pbi_url)),
    '#default_value' => variable_get('pbi_client_id', ''),
    '#required' => TRUE,
  );
  $form['administer']['pbi_client_secret'] = array(
    '#type' => 'textfield',
    '#title' => t('Power BI Application Secret'),
    '#description' => t('Enter your <a href="@power-bi">Power BI</a> registered application secret.', array('@power-bi' => $pbi_url)),
    '#default_value' => variable_get('pbi_client_secret', ''),
    '#required' => true,
  );
  $form['administer']['pbi_group_id'] = array(
    '#type' => 'textfield',
    '#title' => t('Power BI Group ID'),
    '#description' => t('Enter your <a href="@power-bi">Power BI</a> group ID.', array('@power-bi' => $pbi_url)),
    '#default_value' => variable_get('pbi_group_id', ''),
    '#required' => TRUE,
  );
  $form['administer']['pbi_password'] = array(
    '#type' => 'password',
    '#title' => t('Power BI Master account password'),
    '#description' => t('Enter your <a href="@power-bi">Power BI</a> master account password, saved password will not be shown here.', array('@power-bi' => $pbi_url)),
  );
  $form['site']['item-check'] = array(
    '#type' => 'fieldset',
    '#group' => 'site',
    '#title' => t('Debug mode'),
    '#description' => t('Enable debugging mode, development purpose only.'),
  );
  $form['site']['item-check']['bpi_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable debug mode'),
    '#default_value' => variable_get('bpi_debug', 0),
  );
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  return $form;
}

/**
 * Power BI settings form submit handler.
 */
function powerbi_settings_form_submit($form_id, $form_values) {

  $pbi_username = $form_values['values']['pbi_username'];
  $pbi_group_id = $form_values['values']['pbi_group_id'];
  $pbi_password = $form_values['values']['pbi_password'];
  $pbi_client_id = $form_values['values']['pbi_client_id'];
  $pbi_client_secret = $form_values['values']['pbi_client_secret'];
  $bpi_debug = $form_values['values']['bpi_debug'];

  // Set value in variable table.
  variable_set('pbi_username', $pbi_username);
  variable_set('pbi_group_id', $pbi_group_id);
  if (!empty($pbi_password)) {
    variable_set('pbi_password', $pbi_password);
  }
  variable_set('pbi_client_id', $pbi_client_id);
  variable_set('pbi_client_secret', $pbi_client_secret);
  variable_set('bpi_debug', $bpi_debug);
  drupal_set_message(t('The settings has been saved.'));
}
