var time;
var seconds = 0;
var minutes = 0;
var hours = 0;
var enabled = 1;
var delayed = 0;

/**
 * Start the timer when the script is loaded.
 */
timer();

/**
 * Throw warning if user navigates away from page without saving timer
 * information
 */
jQuery(document).ready(function() {
  if (Drupal.settings.support_timer.unload_warning) {
    jQuery('#comment-form').bind("change", function() { confirm_unload(true); });
    jQuery('#node-form').bind("change", function() { confirm_unload(true); });
    jQuery("#edit-submit").click(function() { window.confirm_unload(false); });
    jQuery("#edit-preview").click(function() { window.confirm_unload(false); });
  }
});

/**
 * Allow user to start or stop the timer.
 */
function pause_timer() {
  if (enabled) {
    enabled = 0;
    window.setTimeout(function() {
      delay();
    }, 1000);
    // Replace "Pause" with "Resume".
    jQuery("#edit-pause")[0].value = "Resume";
  }
  else {
    if (delayed) {
      enabled = 1;
      delayed = 0;
      timer();
      // Replace "Resume" with "Pause".
      jQuery("#edit-pause")[0].value = "Pause";
    }
  }
}

/**
 * Prevent multiple timers from starting at once.
 */
function delay() {
  delayed++;
}

/**
 * Reset all counters, starting the timer over at 00:00:00.
 */
function reset_timer() {
  seconds = 0;
  minutes = 0;
  hours = 0;
  display_time();
}

/**
 * Update the edit-elapsed textfield with the current elapsed time.
 */
function display_time() {
  if (hours < 10) {
    time = '0'+hours;
  }
  else {
    time = hours;
  }
  if (minutes < 10) {
    time += ':0'+minutes;
  }
  else {
    time += ':'+minutes;
  }
  if (seconds < 10) {
    time += ':0'+seconds;
  }
  else {
    time += ':'+seconds;
  }
  jQuery(document).ready(function() {
    jQuery("#edit-elapsed").val(time);
  });
}

/**
 * Get time from Time spent (elapsed) field.
 */
function get_time() {
  if ((Drupal.settings.support_timer != undefined) &&
      (Drupal.settings.support_timer.elapsed != undefined)) {
    // reloaded after a preview, use passed in value
    gettime = Drupal.settings.support_timer.elapsed;
    Drupal.settings.support_timer.elapsed = undefined;
  }
  else {
    gettime = jQuery("#edit-elapsed").val();
  }
  if (gettime != undefined) {
    pieces = gettime.split(':');
    hours = parseInt(pieces[0], 10);
    minutes = parseInt(pieces[1], 10);
    seconds = parseInt(pieces[2], 10);
  }
}

/**
 * Count seconds.
 */
function timer() {
  if (!enabled) {
    return false;
  }
  get_time();
  seconds += 1;
  if (seconds >= 60) {
    seconds = 0;
    minutes++;
  }
  if (minutes >= 60) {
    minutes = 0;
    hours++;
  }
  display_time();
  window.setTimeout(function() {
    timer();
  }, 1000);
}

/**
 * Determine whether or not we should display a message when a user navigates
 * away from the current page.
 */
function confirm_unload(on) {
  window.onbeforeunload = (on) ? unload_message : null;
}

/**
 * The message we display when a user navigates away from a changed ticket
 * without saving his/her changes.
 */
function unload_message() {
  return Drupal.t('Any timer information you have entered for this support ticket will be lost if you navigate away from this page without pressing the Save button.');
}
