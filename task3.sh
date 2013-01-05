./bmpHeaderDataSplit ../data/im0.bmp
./bmpHeaderDataSplit ../data/im1.bmp
./bmpHeaderDataSplit ../data/im2.bmp

./task3 0.0 t3_out_0dB.bmp.data ../data/im0.bmp.data ../data/im1.bmp.data ../data/im2.bmp.data
./task3 10.0 t3_out_10dB.bmp.data ../data/im0.bmp.data ../data/im1.bmp.data ../data/im2.bmp.data
./task3 20.0 t3_out_20dB.bmp.data ../data/im0.bmp.data ../data/im1.bmp.data ../data/im2.bmp.data
./task3 40.0 t3_out_40dB.bmp.data ../data/im0.bmp.data ../data/im1.bmp.data ../data/im2.bmp.data

mkdir task3_results
./bmpHeaderDataMerge task3_results/im0_received_0dB.bmp ../data/im0.bmp.header t3_out_0dB.bmp.data
./bmpHeaderDataMerge task3_results/im0_received_10dB.bmp ../data/im0.bmp.header t3_out_10dB.bmp.data
./bmpHeaderDataMerge task3_results/im0_received_20dB.bmp ../data/im0.bmp.header t3_out_20dB.bmp.data
./bmpHeaderDataMerge task3_results/im0_received_40dB.bmp ../data/im0.bmp.header t3_out_40dB.bmp.data

rm ../data/im*.bmp.*
rm ./t3_out_*dB.bmp.data
