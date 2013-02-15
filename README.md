# Turnip

Turnip is OpenSourcery's Drupal starting kit.

![Turnip](https://upload.wikimedia.org/wikipedia/commons/thumb/a/a9/Turnip_J1.jpg/320px-Turnip_J1.jpg)

## Installation

1. Run `bin/make-install-profile` to instantiate an installation profile. For example
   ```
   bin/make-install-profile my_profile my_theme "Short name" "Long name"
   ```
1. Customize `my_profile/my_profile.make`
1. Run `bin/rebuild`
1. Custom modules or features should go in `my_project/modules/custom` or `my_project/modules/features`.
