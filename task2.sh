./bmpHeaderDataSplit ../data/im0.bmp
./bmpHeaderDataSplit ../data/im1.bmp
./bmpHeaderDataSplit ../data/im2.bmp

./task2 0.0 t2_out_0dB.bmp.data ../data/im0.bmp.data ../data/im1.bmp.data ../data/im2.bmp.data
./task2 10.0 t2_out_10dB.bmp.data ../data/im0.bmp.data ../data/im1.bmp.data ../data/im2.bmp.data
./task2 20.0 t2_out_20dB.bmp.data ../data/im0.bmp.data ../data/im1.bmp.data ../data/im2.bmp.data
./task2 40.0 t2_out_40dB.bmp.data ../data/im0.bmp.data ../data/im1.bmp.data ../data/im2.bmp.data

mkdir task2_results
./bmpHeaderDataMerge task2_results/im0_received_0dB.bmp ../data/im0.bmp.header t2_out_0dB.bmp.data
./bmpHeaderDataMerge task2_results/im0_received_10dB.bmp ../data/im0.bmp.header t2_out_10dB.bmp.data
./bmpHeaderDataMerge task2_results/im0_received_20dB.bmp ../data/im0.bmp.header t2_out_20dB.bmp.data
./bmpHeaderDataMerge task2_results/im0_received_40dB.bmp ../data/im0.bmp.header t2_out_40dB.bmp.data

rm ../data/im*.bmp.*
rm ./t2_out_*dB.bmp.data
