/**
 * @file
 */

(function ($) {
  Drupal.behaviors.powerBI = {

    attach: function (context, settings) {
      var embedConfiguration = {
        type: settings.display,
        id: settings.powerBI.value[0].id,
        embedUrl: settings.powerBI.value[0].embedUrl,
        //pageName: 'ReportSection',
        settings: {
          navContentPaneEnabled: false
        },
        accessToken: settings.accessToken,
      };
      var $reportContainer = $('#reportContainer');
      if (settings.powerBI.value[0].embedUrl) {
        var report = powerbi.embed($reportContainer.get(0), embedConfiguration);
      }
      else {
        console.log('Embed Url is missing');
      }
      // Enable debugging mode.
      if (settings.debug) {
        console.log(settings.powerBI.value);
      }
    }
  };
}(jQuery));
