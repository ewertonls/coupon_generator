BCHMRK_SRC = main.c bench/bench_tools.c coupon/coupon_generator.c

build_dbg:
	clang -I./bench -I./coupon -g -O0 $(BCHMRK_SRC) -o coupon_bench_dbg

build:
	clang -I./bench -I./coupon -O3 $(BCHMRK_SRC) -o coupon_bench

clean:
	rm -f coupon_bench_dbg && rm coupon_bench