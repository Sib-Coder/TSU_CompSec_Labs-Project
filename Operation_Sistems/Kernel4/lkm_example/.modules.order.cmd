cmd_/usr/src/lkm_example/modules.order := {   echo /usr/src/lkm_example/lkm_example.ko; :; } | awk '!x[$$0]++' - > /usr/src/lkm_example/modules.order
