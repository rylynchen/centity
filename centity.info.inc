<?php

/**
 * Extend the defaults.
 */
class CentityMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];
    $properties['cid'] = array(
      'label' => t('Centity ID'),
      'description' => t('The {centity}.cid.'),
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer centities',
      'schema field' => 'cid',
    );
    $properties['type'] = array(
      'label' => t('Type'),
      'description' => t('The {centity}.type.'),
      'setter callback' => 'entity_property_verbatim_set',
      'setter permission' => 'administer centities',
      'schema field' => 'type',
    );
    return $info;
  }
}