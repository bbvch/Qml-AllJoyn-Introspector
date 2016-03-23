TEMPLATE = subdirs

SUBDIRS = \
	core \
	application \
        ajintrospect

!android {
    SUBDIRS += test
}

application.depends = \
	core \
        ajintrospect

test.depends = \
	core

DISTFILES += \
        README.md
