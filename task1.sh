./bmpHeaderDataSplit ../data/im0.bmp
./bmpHeaderDataSplit ../data/im1.bmp
./bmpHeaderDataSplit ../data/im2.bmp

./task1 0.0 t1_out_0dB.bmp.data ../data/im0.bmp.data ../data/im1.bmp.data ../data/im2.bmp.data
./task1 10.0 t1_out_10dB.bmp.data ../data/im0.bmp.data ../data/im1.bmp.data ../data/im2.bmp.data
./task1 20.0 t1_out_20dB.bmp.data ../data/im0.bmp.data ../data/im1.bmp.data ../data/im2.bmp.data
./task1 40.0 t1_out_40dB.bmp.data ../data/im0.bmp.data ../data/im1.bmp.data ../data/im2.bmp.data

mkdir task1_results
./bmpHeaderDataMerge task1_results/im0_received_0dB.bmp ../data/im0.bmp.header t1_out_0dB.bmp.data
./bmpHeaderDataMerge task1_results/im0_received_10dB.bmp ../data/im0.bmp.header t1_out_10dB.bmp.data
./bmpHeaderDataMerge task1_results/im0_received_20dB.bmp ../data/im0.bmp.header t1_out_20dB.bmp.data
./bmpHeaderDataMerge task1_results/im0_received_40dB.bmp ../data/im0.bmp.header t1_out_40dB.bmp.data

rm ../data/im*.bmp.*
rm ./t1_out_*dB.bmp.data
