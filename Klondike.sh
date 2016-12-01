SCRIPTDIR=`dirname "$(readlink -f "$0")"`

echo $SCRIPTDIR
pushd .
cd $SCRIPTDIR
LD_LIBRARY_PATH=$SCRIPTDIR ./Program
popd
