<?php

/**
 * @file
 * Template for menu item content.
 *
 * - $debug boolean TRUE or FALSE.
 * - $response contains data returned form power bi service call.
 */
drupal_add_css(drupal_get_path('module', 'powerbi') . '/css/powerbi.css');
drupal_add_js(drupal_get_path('module', 'powerbi') . '/js/powerbi.js');
drupal_add_js(drupal_get_path('module', 'powerbi') . '/js/powerbi.local.js');

?>
<div id="reportContainer"></div>
<?php if ($response && $debug) {
  print '<div id="debug-section">';
    echo json_encode($response, JSON_PRETTY_PRINT);
  print "</div>";
}?>

