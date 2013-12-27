<div class="<?php echo $classes; ?> clearfix"<?php echo $attributes; ?>>
  <?php if (!$page): ?>
    <h2 <?php echo $title_attributes; ?>>
      <a href="<?php echo $url; ?>"><?php echo $title; ?></a>
    </h2>
  <?php endif; ?>
  <div class="content"<?php echo $content_attributes; ?>>
    <?php echo render($content); ?>
  </div>
</div>