; Demo content make file
core = "7.x"
api = 2

projects[entity][subdir] = "development"
projects[entity][version] = "1.0-rc3"

projects[entity_dependency][subdir] = "development"
projects[entity_dependency][download][type] = "git"
projects[entity_dependency][download][revision] = "7ca711a"

projects[deploy][subdir] = "development"
projects[deploy][download][type] = "git"
projects[deploy][download][revision] = "0e88d63"

projects[uuid][subdir] = "development"
projects[uuid][download][type] = "git"
projects[uuid][download][revision] = "bf06527"
