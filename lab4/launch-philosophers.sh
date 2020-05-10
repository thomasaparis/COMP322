#bashscript
SEATS=$1
PROGRAM=./dining-p
POS=$2
CT=1
while [ ${CT} -le ${POS} ] ; do
      ${PROGRAM} ${SEATS} ${CT} &
      echo "Philosopher [${CT}]'s is PID:" $!
      CT=$(( $CT + 1 ))
done
