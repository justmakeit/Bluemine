<?php
// $Id:$

?>
<div data-role="page" id="<?php print $jqm_page_id ?>" data-theme="<?php print $page_data_theme ?>">

  <div data-role="header">
    <h1><?php print $title ? $title : $site_name;  ?></h1>
    <?php if (!$is_front): ?>
    <a href="<?php print $front_page ?>" data-role="button" data-icon="back" class="ui-btn-right">Home</a>
    <?php endif; ?>
    <?php if (isset($tabs) && $tabs): ?>
      <div data-role="navbar">
        <?php print render($tabs); ?>
      </div><!-- /navbar -->
    <?php endif; ?>
  </div> <!-- /data-role="header" -->

  <div data-role="content" data-theme="<?php print $jqm_content_data_theme ?>">
    <?php if ($show_messages && $messages): print $messages; endif; ?>
    <?php print render($page['content']) ?>
    <?php print render($page['content_bottom']); ?>
  </div> <!-- /data-role="content" -->

  <div data-role="footer" class="footer">
    <h1>Footer Content</h1>
    <?php print render($page['footer']) ?>
  </div> <!-- /data-role="footer" -->

</div> <!-- /data-role="page" -->

<!-- /page.tpl.boundary -->