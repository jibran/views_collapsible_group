<?php

/**
 * @file
 * Contains the collapsible default style plugin.
 */

/**
 * Default style plugin to render rows one after another with no
 * decorations.
 *
 * @ingroup views_style_plugins
 */
class views_plugin_style_collapsible_group_defualt extends views_plugin_style_default {

  /**
   * Create options form
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    if ($this->uses_fields() && $this->definition['uses grouping']) {
      $options = array('' => t('- None -'));
      $field_labels = $this->display->handler->get_field_labels(TRUE);
      $options += $field_labels;
      $c = count($this->options['grouping']);
      // Add a form for every grouping, plus one.
      for ($i = 0; $i <= $c; $i++) {
        $grouping = !empty($this->options['grouping'][$i]) ? $this->options['grouping'][$i] : array();
        $grouping += array('collapsible' => FALSE, 'collapsed' => FALSE);
        $form['grouping'][$i]['collapsible'] = array(
          '#type' => 'checkbox',
          '#title' => t('Make the group collapsible'),
          '#default_value' => $grouping['collapsible'],
          '#states' => array(
            'invisible' => array(
              ':input[name="style_options[grouping][' . $i . '][field]"]' => array('value' => ''),
            ),
          ),
          '#attributes' => array(
            'class' => array(
              'dependent-options',
            ),
          ),
        );
        $form['grouping'][$i]['collapsed'] = array(
          '#type' => 'checkbox',
          '#title' => t('Show the group collapsed'),
          '#default_value' => $grouping['collapsed'],
          '#states' => array(
            'invisible' => array(
              ':input[name="style_options[grouping][' . $i . '][collapsible]"]' => array('checked' => FALSE),
            ),
          ),
          '#attributes' => array(
            'class' => array(
              'dependent-options',
            ),
          ),
        );
      }
    }
  }

  /**
   * Render the grouping sets.
   *
   * Plugins may override this method if they wish some other way of handling
   * grouping.
   *
   * @param array $sets
   *   Array containing the grouping sets to render.
   * @param integer $level
   *   Integer indicating the hierarchical level of the grouping.
   *
   * @return string
   *   Rendered output of given grouping sets.
   */
  function render_grouping_sets($sets, $level = 0) {
    $output = '';
    foreach ($sets as $set) {
      $row = reset($set['rows']);
      // Render as a grouping set.
      if (is_array($row) && isset($row['group'])) {
        $output .= theme(views_theme_functions('views_collapsible_group_view_grouping', $this->view, $this->display),
          array(
            'view' => $this->view,
            'grouping' => $this->options['grouping'][$level],
            'grouping_level' => $level,
            'rows' => $set['rows'],
            'title' => $set['group'],
          )
        );
      }
      // Render as a record set.
      else {
        if ($this->uses_row_plugin()) {
          foreach ($set['rows'] as $index => $row) {
            $this->view->row_index = $index;
            $set['rows'][$index] = $this->row_plugin->render($row);
          }
        }

        $output .= theme($this->theme_functions(),
          array(
            'view' => $this->view,
            'options' => $this->options,
            'grouping_level' => $level,
            'rows' => $set['rows'],
            'title' => $set['group'])
        );
      }
    }
    unset($this->view->row_index);
    return $output;
  }

}
