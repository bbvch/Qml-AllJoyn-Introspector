TEMPLATE = subdirs

SUBDIRS = \
	core \
	application \
	ajintrospect \
	test

application.depends = \
	core \
        ajintrospect

test.depends = \
	core

DISTFILES += \
        README.md
