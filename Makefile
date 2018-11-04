# generated files
PLOTSCRIPTS=plotscript_delta.gpl plotscript_lambda.gpl
RESULTS= d_1.000000_l_0.000000_GSResidual_100.txt d_10.000000_l_0.000000_GSResidual_100.txt d_50.000000_l_0.000000_GSResidual_100.txt d_100.000000_l_0.000000_GSResidual_100.txt d_500.000000_l_0.000000_GSResidual_100.txt d_1000.000000_l_0.000000_GSResidual_100.txt d_5000.000000_l_0.000000_GSResidual_100.txt d_10000.000000_l_0.000000_GSResidual_100.txt d_50000.000000_l_0.000000_GSResidual_100.txt d_100000.000000_l_0.000000_GSResidual_100.txt d_1.000000_l_1.000000_GSResidual_100.txt d_1.000000_l_10.000000_GSResidual_100.txt d_1.000000_l_50.000000_GSResidual_100.txt d_1.000000_l_100.000000_GSResidual_100.txt d_1.000000_l_500.000000_GSResidual_100.txt d_1.000000_l_1000.000000_GSResidual_100.txt d_1.000000_l_5000.000000_GSResidual_100.txt d_1.000000_l_10000.000000_GSResidual_100.txt d_1.000000_l_50000.000000_GSResidual_100.txt d_1.000000_l_100000.000000_GSResidual_100.txt d_1.000000_l_0.000000_GSsolution_100.txt d_10.000000_l_0.000000_GSsolution_100.txt d_50.000000_l_0.000000_GSsolution_100.txt d_100.000000_l_0.000000_GSsolution_100.txt d_500.000000_l_0.000000_GSsolution_100.txt d_1000.000000_l_0.000000_GSsolution_100.txt d_5000.000000_l_0.000000_GSsolution_100.txt d_10000.000000_l_0.000000_GSsolution_100.txt d_50000.000000_l_0.000000_GSsolution_100.txt d_100000.000000_l_0.000000_GSsolution_100.txt d_1.000000_l_1.000000_GSsolution_100.txt d_1.000000_l_10.000000_GSsolution_100.txt d_1.000000_l_50.000000_GSsolution_100.txt d_1.000000_l_100.000000_GSsolution_100.txt d_1.000000_l_500.000000_GSsolution_100.txt d_1.000000_l_1000.000000_GSsolution_100.txt d_1.000000_l_5000.000000_GSsolution_100.txt d_1.000000_l_10000.000000_GSsolution_100.txt d_1.000000_l_50000.000000_GSsolution_100.txt d_1.000000_l_100000.000000_GSsolution_100.txt
#RESULTS=result.dat
PROGRAM=sparsematrix
OBJS=main.o sparsematrix.o
PLOTS=Gauss_Seidel_delta.pdf Gauss_Seidel_lambda.pdf

# additional variables
CPPFLAGS=-std=c++11


all: $(PLOTS)


$(PLOTS): $(RESULTS) $(PLOTSCRIPTS)
	gnuplot plotscript_delta.gpl
	gnuplot plotscript_lambda.gpl


$(RESULTS): $(PROGRAM)
	./$(PROGRAM)

$(PROGRAM): $(OBJS)
	g++ $(CPPFLAGS) $(OBJS) -o $(PROGRAM)

$(OBJS): %.o: %.cc
	g++ -O3 -Wall -Wfatal-errors -pedantic $(CPPFLAGS) -c $^ -o $@


clean:
	rm -rf $(OBJS) $(PROGRAM) $(RESULTS)
