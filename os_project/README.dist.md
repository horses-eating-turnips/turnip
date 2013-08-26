OS Project Makefiles
=====================

# Base
Specification of Drupal core and contrib projects used in most builds.

# Demo
There are two ways to get demo/starter content into Features such that revisionable entities can be deployed using the normal Features workflow. The first is by using [UUID Features Integration](https://drupal.org/project/uuid_features), the other method is using [Deploy](https://drupal.org/project/deployment) and [UUID](https://drupal.org/project/uuid) to create fetch-only plans.

The UUID Features workflow is arguably simpler, but out of the box only supports core and a few contrib entity types (nodes, terms, beans, etc). For more general entity exporting Deploy provides a more compressed workflow that could be executed via the UI.

A comparison of the two methods can be found at http://drupal.org/node/1982890.

The demo content feature is an implementation of Deploy-UUID based method.

## Usage
To use this demo content feature, do not make it a dependency in your main makefile or .info file, you want to enable in your install profile, perform install/revert, then turn it off. This is due to the timing of executing the content deployment with respect to the timing of Profiler deploying nodes. This could likely be averted if we were able to move all content deployment to the Deploy-UUID method instead of Profiler. But at the current stage of OS process, we are still using both.

For an example of how to use this in an install profile, see Acumed's [installer include file](https://github.com/opensourcery/Acumed/blob/master/acumed/acumed.install.inc). Generally, this module/feature would never be used in production, except perhaps on an initial deployment to a production server.

Note that in order to deploy content in this fashion, entity types, i.e. node types, vocab terms structures, etc. must be exported separately so that deploy may just drop this entity data in with the backing data structures already in place. This is unlike the uuid_features method where the entity types and fields were part of the same export that included the instances.

## Workflow
For the first export, enable the demo content feature and the `deploy_ui` module. Then, head to the content listing screen in the UI (admin/content). Check the box in the associated row for each node you want to export, then select "Add to demo content" from the ops drop down, then click submit. Deploy and UUID will iterate each node, drill down through entity references, terms, etc, and generate the deploy plan in the database. Note the simplification here in that you only need to make an effort to export nodes, all embedded or referent entities are automatically detected.

Next, you just need to update the feature. A `drush features-update myproject_demo_content` command will export the plan to the demo content feature.

## Gotchas
This method works very well for relatively simple builds. For example, a bunch of blog posts with some terms and image fields would work great. However once we get into more complex data structures, there is more

### Field Collection
If your build will make use of Field Collection, then you will have some problems, depending upon how you use them. The first problem is that Deploy exports referent entities before the referencing entities themselves. With Field Collection, you find yourself in a chicken-egg state in that when reverting an export containing Field Collections, the FC module's save function wants to know who the host entity is during save. Since the FC is exported first, there is no known host entity yet. This problem was worked around with a [custom module](https://github.com/opensourcery/Acumed/tree/master/acumed/modules/custom/field_collection_deploy_helper) for the Acumed build.

Another problem that is currently unsolved is when a field collection contains an entity reference, the export/import cycle breaks down, and interferes with FC expoprts that do not contain entity references. Meaning FCs get crossed up and the whole process just goes sideways.

The lesson here in the current state is that if you are using FCs containing entity references, just don't do it. If not, you might be ok.

### Menu Items
When using profiler to specify nodes and terms, we are able to also specify menu items and heirarchy. Menu items are not directly supported by the Deploy-UUID workflow. But writing simple calls to `menu_link_save` after UUID content has been deployed is likely just as simple. Again, see Acumed's [installer include file](https://github.com/opensourcery/Acumed/blob/master/acumed/acumed.install.inc) for example usage.

### Issues to Watch
* Entiy dependencies and target types: https://drupal.org/node/1545278
* UUID Support for Field Collection: https://drupal.org/node/1817956

# Images
Baisc platform for image management including `media` and `file_entity`.

# Panels
Basic platform for panels usage.

# Solr
Basic platform for search_api or apachesolr.
