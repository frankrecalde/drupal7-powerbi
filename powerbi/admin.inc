<?php

/**
 * @file
 * Contains custom functions for power BI.
 */

require_once 'PowerBiService.php';

/**
 * Get dashboard data from PBI using service call and assign in response.
 */
function pbi_get_dashboard($method, $display) {
  $url = "https://api.powerbi.com/v1.0/myorg/groups/";

  $powerbi = new PowerBiService();
  $embedData = $powerbi->getembeddedURL($url, $method, $display);
  $debuMode = variable_get('bpi_debug', 0);
  $content[] = array(
    '#theme' => 'get-pbi-dashboard',
    '#debug' => $debuMode,
    '#response' => $embedData,
  );
  // Get access token from cookie instead of making call to the server.
  $access_token = (isset($_COOKIE["access_token"])) ? $_COOKIE["access_token"] : $powerbi->getAccessToken();
  $data = array(
    'powerBI' => $embedData,
    'accessToken' => $access_token,
    'debug' => $debuMode,
    'display' => 'dashboard'
  );
  drupal_add_js($data, 'setting');
  return $content;
}

function pbi_get_reports($method, $display) {
  $url = "https://api.powerbi.com/v1.0/myorg/groups/";

  $powerbi = new PowerBiService();
  $embedData = $powerbi->getembeddedURL($url, $method, $display);
  $debuMode = variable_get('bpi_debug', 0);
  $content[] = array(
    '#theme' => 'get-pbi-reports',
    '#debug' => $debuMode,
    '#response' => $embedData,
  );
  // Get access token from cookie instead of making call to the server.
  $access_token = (isset($_COOKIE["access_token"])) ? $_COOKIE["access_token"] : $powerbi->getAccessToken();
  $data = array(
    'powerBI' => $embedData,
    'accessToken' => $access_token,
    'debug' => $debuMode,
    'display' => 'report'
  );
  drupal_add_js($data, 'setting');
  return $content;
}
