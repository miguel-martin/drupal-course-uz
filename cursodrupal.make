core = 7.x
api = 2


####  Specific version
# projects[views] = 3.11

#### More data
# projects[views][version] = 3.11
# projects[views][subdir] = contrib

#### Last version
# projects[views][]
# o
# projects[views][subdir] = contrib

#### Patches
# projects[nodequeue][subdir] = contrib
# projects[nodequeue][version] = 2.0-alpha1
# projects[nodequeue][patch][] = "http://drupal.org/files/issues/1023606-qid-to-name-6.patch"
# projects[nodequeue][patch][] = "http://drupal.org/files/issues/nodequeue_d7_autocomplete-872444-6.patch"

#### From custom
# projects[core_base][type] = "module"
# projects[core_base][subdir] = "features"
# projects[core_base][download][type] = "git"
# projects[core_base][download][url] = "git@bitbucket.org:miuser/mi-feature-base.git"

#### Externas libraries
# libraries[tinymce][download][type] = get
# libraries[tinymce][download][url] = http://download.ephox.com/tinymce/community/tinymce_4.3.13.zip
# libraries[tinymce][destination] = libraries

# DOC: https://www.drupal.org/node/1432374
# drush make <file> -y --contrib-destination --no-core
