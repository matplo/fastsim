from math import exp

from math import tanh

class test:
	def value(self,index,in0,in1,in2):
		self.input0 = (in0 - 0.459987)/0.0509152
		self.input1 = (in1 - 0.188581)/0.0656804
		self.input2 = (in2 - 134.719)/16.5033
		if index==0: return self.neuron0x7fe7d5f097d0();
		return 0.
	def neuron0x7fe7d5f07260(self):
		return self.input0
	def neuron0x7fe7d5f07460(self):
		return self.input1
	def neuron0x7fe7d5f07760(self):
		return self.input2
	def neuron0x7fe7d5f07b80(self):
		input = 0.418061
		input = input + self.synapse0x7fe7d5f04680()
		input = input + self.synapse0x7fe7d5f06ad0()
		input = input + self.synapse0x7fe7d5df4a90()
		if input<-709. : return 0
		return ((1/(1+exp(-input)))*1)+0
	def neuron0x7fe7d5f07e00(self):
		input = 0.140628
		input = input + self.synapse0x7fe7d5f07220()
		input = input + self.synapse0x7fe7d5f07180()
		input = input + self.synapse0x7fe7d5f071b0()
		if input<-709. : return 0
		return ((1/(1+exp(-input)))*1)+0
	def neuron0x7fe7d5f08100(self):
		input = 1.26102
		input = input + self.synapse0x7fe7d5f08400()
		input = input + self.synapse0x7fe7d5f08430()
		input = input + self.synapse0x7fe7d5f08460()
		if input<-709. : return 0
		return ((1/(1+exp(-input)))*1)+0
	def neuron0x7fe7d5f08490(self):
		input = -0.716779
		input = input + self.synapse0x7fe7d5f08790()
		input = input + self.synapse0x7fe7d5f087c0()
		input = input + self.synapse0x7fe7d5f087f0()
		if input<-709. : return 0
		return ((1/(1+exp(-input)))*1)+0
	def neuron0x7fe7d5f08820(self):
		input = 1.14511
		input = input + self.synapse0x7fe7d5f08b20()
		input = input + self.synapse0x7fe7d5f08b50()
		input = input + self.synapse0x7fe7d5f08b80()
		if input<-709. : return 0
		return ((1/(1+exp(-input)))*1)+0
	def neuron0x7fe7d5f08bb0(self):
		input = -0.547708
		input = input + self.synapse0x7fe7d5f08eb0()
		input = input + self.synapse0x7fe7d5f08ee0()
		input = input + self.synapse0x7fe7d5f070c0()
		input = input + self.synapse0x7fe7d5f09010()
		input = input + self.synapse0x7fe7d5f09040()
		if input<-709. : return 0
		return ((1/(1+exp(-input)))*1)+0
	def neuron0x7fe7d5f09070(self):
		input = -0.277645
		input = input + self.synapse0x7fe7d5f092f0()
		input = input + self.synapse0x7fe7d5f09320()
		input = input + self.synapse0x7fe7d5f09350()
		input = input + self.synapse0x7fe7d5f09380()
		input = input + self.synapse0x7fe7d5f093b0()
		if input<-709. : return 0
		return ((1/(1+exp(-input)))*1)+0
	def neuron0x7fe7d5f093e0(self):
		input = 0.20342
		input = input + self.synapse0x7fe7d5f096e0()
		input = input + self.synapse0x7fe7d5f09710()
		input = input + self.synapse0x7fe7d5f09740()
		input = input + self.synapse0x7fe7d5f09770()
		input = input + self.synapse0x7fe7d5f097a0()
		if input<-709. : return 0
		return ((1/(1+exp(-input)))*1)+0
	def neuron0x7fe7d5f097d0(self):
		input = 2.93581
		input = input + self.synapse0x7fe7d5f099d0()
		input = input + self.synapse0x7fe7d5f09a00()
		input = input + self.synapse0x7fe7d5f09a30()
		return (input*1)+0
	def synapse0x7fe7d5f04680(self):
		return (self.neuron0x7fe7d5f07260()*0.869072)
	def synapse0x7fe7d5f06ad0(self):
		return (self.neuron0x7fe7d5f07460()*-2.43359)
	def synapse0x7fe7d5df4a90(self):
		return (self.neuron0x7fe7d5f07760()*0.118506)
	def synapse0x7fe7d5f07220(self):
		return (self.neuron0x7fe7d5f07260()*0.176454)
	def synapse0x7fe7d5f07180(self):
		return (self.neuron0x7fe7d5f07460()*-0.00214223)
	def synapse0x7fe7d5f071b0(self):
		return (self.neuron0x7fe7d5f07760()*0.842961)
	def synapse0x7fe7d5f08400(self):
		return (self.neuron0x7fe7d5f07260()*-1.20877)
	def synapse0x7fe7d5f08430(self):
		return (self.neuron0x7fe7d5f07460()*0.50362)
	def synapse0x7fe7d5f08460(self):
		return (self.neuron0x7fe7d5f07760()*2.8006)
	def synapse0x7fe7d5f08790(self):
		return (self.neuron0x7fe7d5f07260()*0.241718)
	def synapse0x7fe7d5f087c0(self):
		return (self.neuron0x7fe7d5f07460()*1.69781)
	def synapse0x7fe7d5f087f0(self):
		return (self.neuron0x7fe7d5f07760()*-1.31755)
	def synapse0x7fe7d5f08b20(self):
		return (self.neuron0x7fe7d5f07260()*-0.221285)
	def synapse0x7fe7d5f08b50(self):
		return (self.neuron0x7fe7d5f07460()*1.75274)
	def synapse0x7fe7d5f08b80(self):
		return (self.neuron0x7fe7d5f07760()*-2.79079)
	def synapse0x7fe7d5f08eb0(self):
		return (self.neuron0x7fe7d5f07b80()*1.0459)
	def synapse0x7fe7d5f08ee0(self):
		return (self.neuron0x7fe7d5f07e00()*-1.34307)
	def synapse0x7fe7d5f070c0(self):
		return (self.neuron0x7fe7d5f08100()*0.637177)
	def synapse0x7fe7d5f09010(self):
		return (self.neuron0x7fe7d5f08490()*0.698593)
	def synapse0x7fe7d5f09040(self):
		return (self.neuron0x7fe7d5f08820()*-2.00504)
	def synapse0x7fe7d5f092f0(self):
		return (self.neuron0x7fe7d5f07b80()*0.27258)
	def synapse0x7fe7d5f09320(self):
		return (self.neuron0x7fe7d5f07e00()*-0.247462)
	def synapse0x7fe7d5f09350(self):
		return (self.neuron0x7fe7d5f08100()*0.0553687)
	def synapse0x7fe7d5f09380(self):
		return (self.neuron0x7fe7d5f08490()*0.144554)
	def synapse0x7fe7d5f093b0(self):
		return (self.neuron0x7fe7d5f08820()*-1.64092)
	def synapse0x7fe7d5f096e0(self):
		return (self.neuron0x7fe7d5f07b80()*-1.31409)
	def synapse0x7fe7d5f09710(self):
		return (self.neuron0x7fe7d5f07e00()*2.79002)
	def synapse0x7fe7d5f09740(self):
		return (self.neuron0x7fe7d5f08100()*-1.52655)
	def synapse0x7fe7d5f09770(self):
		return (self.neuron0x7fe7d5f08490()*-1.39688)
	def synapse0x7fe7d5f097a0(self):
		return (self.neuron0x7fe7d5f08820()*3.1267)
	def synapse0x7fe7d5f099d0(self):
		return (self.neuron0x7fe7d5f08bb0()*0.812677)
	def synapse0x7fe7d5f09a00(self):
		return (self.neuron0x7fe7d5f09070()*-3.10084)
	def synapse0x7fe7d5f09a30(self):
		return (self.neuron0x7fe7d5f093e0()*-2.82153)
