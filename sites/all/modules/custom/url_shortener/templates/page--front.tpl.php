
  <div id="header">


    <?php print theme(
      'links__system_main_menu',
      array(
        'links' => $main_menu,
        'attributes' => array(
          'id' => 'main-menu',
          'class' => array(
            'links',
            'inline',
            'clearfix'
          )
        ),
      )
    ); ?>

  </div>


  <div id="wraper">
    <div id="top_part">
      <h1 id="the_logo">
        <img src="<?php print $logo; ?>" alt="<?php print $site_name; ?>">
      </h1>
    </div>


    <div id="middle_part">
      <h2 class="title"><?php print $title; ?></h2>

      <?php print $messages; ?>

      <?php print render($page['content']); ?>
    </div>
  </div>

  <div id="bottom">
    Powered by Drupal <?php print date('Y');?>
  </div>
