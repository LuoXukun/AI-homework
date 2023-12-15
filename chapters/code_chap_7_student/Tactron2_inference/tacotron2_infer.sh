#!/bin/bash
source /torch/venv3/pytorch/bin/activate
BATCH_SIZE=1
INPUT_LENGTH=128
PRECISION="fp32"
NUM_ITERS=23 # extra 3 iterations for warmup
cur_path=$(pwd)
CKPT_DIR="./model/pretrained/"
TACOTRON2_CKPT="${CKPT_DIR}/nvidia_tacotron2pyt_fp32_20190427"
WAVEGLOW_CKPT="${CKPT_DIR}/nvidia_waveglowpyt_fp32_20190427"
AMP_RUN=""
#TEST_PROGRAM="test_infer.py"
TEST_PROGRAM="src/test_infer.py"
# WN_CHANNELS of the pretrained model listed above is 512
#WN_CHANNELS=256
WN_CHANNELS=512
CPU_RUN=""


# parse cmd-line
while [ -n "$1" ]
do
    case "$1" in
	-bs|--batch-size)
	    BATCH_SIZE="$2"
	    shift
	    ;;
	-il|--input-length)
	    INPUT_LENGTH="$2"
	    shift
	    ;;
	-p|--prec)
	    PRECISION="$2"
	    shift
	    ;;
	--num-iters)
	    NUM_ITERS="$2"
	    shift
	    ;;
	--test)
	    TEST_PROGRAM="$2"
	    shift
	    ;;
	--tacotron2)
	    TACOTRON2_CKPT="$2"
	    shift
	    ;;
	--encoder)
	    ENCODER_CKPT="$2"
	    shift
	    ;;
	--decoder)
	    DECODER_CKPT="$2"
	    shift
	    ;;
	--postnet)
	    POSTNET_CKPT="$2"
	    shift
	    ;;
	--waveglow)
	    WAVEGLOW_CKPT="$2"
	    shift
	    ;;
	--wn-channels)
	    WN_CHANNELS="$2"
	    shift
	    ;;
	--cpu-run)
	    CPU_RUN="--cpu-run"
	    shift
	    ;;
	*)
	    echo "Option $1 not recognized"
    esac
    shift
done

# check pretrained_model 
if [ ! -f "${TACOTRON2_CKPT}" ] || [ ! -f "${WAVEGLOW_CKPT}" ]
then
    echo "Pretrained_model is empty, please download as README.md said!"
    exit 1
fi

if [ "$PRECISION" = "amp" ]
then
    AMP_RUN="--amp-run"
elif  [ "$PRECISION" = "fp16" ]
then
    AMP_RUN="--fp16"
fi

LOG_SUFFIX=bs${BATCH_SIZE}_il${INPUT_LENGTH}_${PRECISION}
NVLOG_FILE=nvlog_${LOG_SUFFIX}.json
TMP_LOGFILE=tmp_log_${LOG_SUFFIX}.log
LOGFILE=log_${LOG_SUFFIX}.log


if [ "$TEST_PROGRAM" = "src/trt/test_infer_trt.py" ]
then
    TACOTRON2_PARAMS="--encoder $ENCODER_CKPT --decoder $DECODER_CKPT --postnet $POSTNET_CKPT"
else
    TACOTRON2_PARAMS="--tacotron2 $TACOTRON2_CKPT"
fi

set -x
python $TEST_PROGRAM \
       $TACOTRON2_PARAMS \
       --waveglow $WAVEGLOW_CKPT \
       --batch-size $BATCH_SIZE \
       --input-length $INPUT_LENGTH $AMP_RUN \
       --log-file $NVLOG_FILE \
       --num-iters $NUM_ITERS \
       --wn-channels $WN_CHANNELS \
       $CPU_RUN \
       |& tee $TMP_LOGFILE
set +x


PERF=$(cat $TMP_LOGFILE | grep -F 'Throughput average (samples/sec)' | awk -F'= ' '{print $2}')
NUM_MELS=$(cat $TMP_LOGFILE | grep -F 'Number of mels per audio average' | awk -F'= ' '{print $2}')
LATENCY=$(cat $TMP_LOGFILE | grep -F 'Latency average (seconds)' | awk -F'= ' '{print $2}')
LATENCYSTD=$(cat $TMP_LOGFILE | grep -F 'Latency std (seconds)' | awk -F'= ' '{print $2}')
LATENCY90=$(cat $TMP_LOGFILE | grep -F 'Latency cl 90 (seconds)' | awk -F'= ' '{print $2}')
LATENCY95=$(cat $TMP_LOGFILE | grep -F 'Latency cl 95 (seconds)' | awk -F'= ' '{print $2}')
LATENCY99=$(cat $TMP_LOGFILE | grep -F 'Latency cl 99 (seconds)' | awk -F'= ' '{print $2}')

echo "$BATCH_SIZE,$INPUT_LENGTH,$PRECISION,$NUM_ITERS,$LATENCY,$LATENCYSTD,$LATENCY90,$LATENCY95,$LATENCY99,$PERF,$NUM_MELS" >> $LOGFILE
