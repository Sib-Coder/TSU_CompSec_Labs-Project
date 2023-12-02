cmd_/usr/src/lkm_example/Module.symvers := sed 's/\.ko$$/\.o/' /usr/src/lkm_example/modules.order | scripts/mod/modpost -m -a  -o /usr/src/lkm_example/Module.symvers -e -i Module.symvers   -T -
