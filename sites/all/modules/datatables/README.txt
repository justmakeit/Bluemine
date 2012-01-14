// $Id: README.txt,v 1.1.4.2 2011/01/05 03:45:15 duellj Exp $

This module provides views integration for the DataTables jQuery plugin, which 
provides advanced interaction controls to HTML tables such as dynamic
pagination, on-the-fly filtering, and column sorting.

For full documentation and examples, visit the DataTables jQuery plugin page:
  http://plugins.jquery.com/project/DataTables


-- Installation --

* Copy the datatables module to sites/all/modules directory.

* Download the latest DataTables jQuery plugin 1.6 package from:
    http://plugins.jquery.com/project/DataTables

* Extract the archive and move the dataTables-1.6/media folder to the 
  sub-directory called dataTables in the datatables folder:

    sites/all/modules/datatables/dataTables/

  The final path to the media folder should be:

    sites/all/modules/datatables/dataTables/media

* Enable the module at Administer >> Site building >> Modules.

-- Usage --

* Create a new view at admin/build/views/add

* Add fields to show in the table.

* Select DataTables as the view style.
