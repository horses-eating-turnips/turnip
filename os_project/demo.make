; Demo content make file
core = "7.x"
api = 2

projects[entity_dependency][subdir] = "development"
projects[entity_dependency][download][branch] = "7.x-1.x"
projects[entity_dependency][download][revision] = "7ca711a"

projects[deploy][subdir] = "development"
projects[deploy][download][branch] = "7.x-2.x"
projects[deploy][download][revision] = "4f17cb3"

projects[uuid][subdir] = "development"
projects[uuid][download][branch] = "7.x-1.x"
projects[uuid][download][revision] = "8b6d70f"
