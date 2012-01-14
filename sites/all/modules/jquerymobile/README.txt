jQuery Mobile (http://jquerymobile.com/) is a mobile web presentation framework that aims to provide an improved user experience on a wide range of mobile devices.

See both docs and demos at (http://jquerymobile.com/demos/1.0a3/).

To use this module you must download the jQuery Mobile library (http://jquerymobile.com/download/).

This module is currently written to work with jQuery Mobile 1.0 Alpha 3, with a patch to the JS.

This module is designed to work with a jQuery Mobile-enabled theme, such as XXXXXXXXX. (TBD after/if project is accepted on D.O.)

INSTALLATION INSTRUCTIONS
-------------------------
1. Download the jQuery Mobile file from http://jquerymobile.com/download/ . For the purposes of this module it is recommended you download the zip archive.

2. Unpack the files into a folder called 'jquerymobile' inside the module directory, i.e.

  sites/all/modules/jquerymobile/jquerymobile
  
3. Run the patch included with the module. On a Unix-based system you can run it with the following command:

  patch -p0 < jquery.mobile-1.0a3.js.patch

It is HIGHLY recommended that you run this patch. It improves jQuery Mobile's default behavior for loading external scripts and stylesheets and makes using jQuery Mobile with Drupal much easier; it also makes a few minor fixes.

The patch is currently against jQuery Mobile 1.0 Alpha 3. It is not recommended to patch against future versions as the framework is still in flux. As future versions of the framework are released, this module and patch will be updated accordingly.

USAGE
-----
You can add the necessary files by using the function jquerymobile_add(); for example, within YOURTHEME/template.php:

function YOURTHEME_process_page(&$variables) {
  if (module_exists('jquerymobile')) {
    jquerymobile_add();
  }
}

We recommend using jQM as a base theme in conjunction with the jQueryMobile module. XXXXXXXX (Path to jQM contingent on project being accepted).