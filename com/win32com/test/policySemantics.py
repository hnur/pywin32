import win32com.server.util
import win32com.client
import pythoncom
import winerror

class Error(Exception):
	pass
	
# An object representing a list of numbers
class PythonSemanticClass:
	_public_methods_ = ["In"]  # DISPIDs are allocated.
	_dispid_to_func_ = { 10: 'Add', 11:'Remove'} # DISPIDs specified by the object.
	def __init__(self):
		self.list = []
	def _NewEnum(self):
		return win32com.server.util.NewEnum(self.list)
	def _value_(self):
		# should return an array.
		return self.list
	def _Evaluate(self):
		# return the sum
		return reduce(lambda a,b: a+b, self.list, 0)
	def In(self, value):
		return value in self.list
	def Add(self, value):
		self.list.append(value)
	def Remove(self, value):
		self.list.remove(value)

def DispExTest(ob):
	if not __debug__: print "WARNING: Tests dressed up as assertions are being skipped!"
	assert ob.GetDispID("Add", 0)==10, "Policy did not honour the dispid"
# Not impl	
#	assert ob.GetMemberName(10, 0)=="add", "Policy did not give me the correct function for the dispid"
	assert ob.GetDispID("Remove", 0)==11, "Policy did not honour the dispid"
	assert ob.GetDispID("In", 0)==1000, "Allocated dispid unexpected value"
	assert ob.GetDispID("_NewEnum", 0)==pythoncom.DISPID_NEWENUM, "_NewEnum() got unexpected DISPID"
	dispids = []
	dispid = -1
	while 1:
		try:
			dispid = ob.GetNextDispID(0, dispid)
			dispids.append(dispid)
		except pythoncom.com_error, (hr, desc, exc, arg):
			assert hr==winerror.S_FALSE, "Bad result at end of enum"
			break
	dispids.sort()
	if dispids <> [pythoncom.DISPID_EVALUATE, pythoncom.DISPID_NEWENUM, 10, 11, 1000]:
		raise Error, "Got back the wrong dispids: %s" % dispids
	print "IDispatchEx semantics worked"
		
def SemanticTest(ob):
	# First just check our object "generally" as expected.
	ob.Add(1)
	ob.Add(2)
	ob.Add(3)
	# invoke _value_
	if ob() != (1,2,3):
		raise Error, "Bad result - got %s" % (`ob()`)

	dispob = ob._oleobj_
	
	rc = dispob.Invoke(pythoncom.DISPID_EVALUATE, 0, pythoncom.DISPATCH_METHOD|pythoncom.DISPATCH_PROPERTYGET, 1)
	if rc != 6:
		raise Error, "Evaluate returned", rc

	dispexob = dispob.QueryInterface(pythoncom.IID_IDispatchEx)
	DispExTest(dispexob)
	print "Python policy semantics worked."
	
def TestAll():
	debug=0
	import win32com.server.dispatcher
	if debug:
		dispatcher=win32com.server.dispatcher.DefaultDebugDispatcher
	else:
		dispatcher=None
	disp = win32com.server.util.wrap(PythonSemanticClass(), useDispatcher=dispatcher)
	ob = win32com.client.Dispatch(disp)
	SemanticTest(ob)
	
if __name__=='__main__':
	TestAll()
