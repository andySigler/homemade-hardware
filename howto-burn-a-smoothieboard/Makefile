all:
	xmlto html-nochunks howto-burn-a-smoothie.xml --skip-validation

css:
	xmlto xhtml -m config.xsl howto-burn-a-smoothie.xml --skip-validation

html:
	docbook2html howto-burn-a-smoothie.xml

pdf:
	xsltproc /usr/share/sgml/docbook/xsl-stylesheets/html/docbook.xsl howto-burn-a-smoothie.xml > howto-burn-a-smoothie.fo 
	fop -fo howto-burn-a-smoothie.fo -pdf howto-burn-a-smoothie.pdf
