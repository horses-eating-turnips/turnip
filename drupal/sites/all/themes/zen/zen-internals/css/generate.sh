#!/bin/sh

# $Id: generate.sh,v 1.4.2.1 2009/12/12 15:31:55 johnalbin Exp $
#
# This script is used by the MAINTAINER to generate composite stylesheets for
# the base Zen theme from the stylesheets in the STARTERKIT.

echo -n '/* $' > header.txt;
echo 'Id$ */' >> header.txt;
echo >> header.txt;

cat header.txt ../../STARTERKIT/css/html-reset.css ../../STARTERKIT/css/wireframes.css ../../STARTERKIT/css/layout-fixed.css ../../STARTERKIT/css/page-backgrounds.css ../../STARTERKIT/css/tabs.css ../../STARTERKIT/css/messages.css ../../STARTERKIT/css/pages.css ../../STARTERKIT/css/block-editing.css ../../STARTERKIT/css/blocks.css ../../STARTERKIT/css/navigation.css ../../STARTERKIT/css/panels-styles.css ../../STARTERKIT/css/views-styles.css ../../STARTERKIT/css/nodes.css ../../STARTERKIT/css/comments.css ../../STARTERKIT/css/forms.css ../../STARTERKIT/css/fields.css | perl -e 'while(<>) { $_ =~ s|^\/\* \$(Id: [^\$]+) \$|\/* \1|; print $_; }' - > zen-fixed.css;

cat header.txt ../../STARTERKIT/css/html-reset.css ../../STARTERKIT/css/wireframes.css ../../STARTERKIT/css/layout-liquid.css ../../STARTERKIT/css/page-backgrounds.css ../../STARTERKIT/css/tabs.css ../../STARTERKIT/css/messages.css ../../STARTERKIT/css/pages.css ../../STARTERKIT/css/block-editing.css ../../STARTERKIT/css/blocks.css ../../STARTERKIT/css/navigation.css ../../STARTERKIT/css/panels-styles.css ../../STARTERKIT/css/views-styles.css ../../STARTERKIT/css/nodes.css ../../STARTERKIT/css/comments.css ../../STARTERKIT/css/forms.css ../../STARTERKIT/css/fields.css | perl -e 'while(<>) { $_ =~ s|^\/\* \$(Id: [^\$]+) \$|\/* \1|; print $_; }' - > zen-liquid.css

rm header.txt;

cp ../../STARTERKIT/css/print.css .;

cp ../../STARTERKIT/css/ie.css .;
cp ../../STARTERKIT/css/ie6.css .;
