cmd_/home/sib/src/lkm_example/modules.order := {   echo /home/sib/src/lkm_example/lkm_example.ko; :; } | awk '!x[$$0]++' - > /home/sib/src/lkm_example/modules.order
