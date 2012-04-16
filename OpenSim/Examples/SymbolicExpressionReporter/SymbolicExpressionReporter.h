#ifndef _SymbolicExpressionReporter_h_
#define _SymbolicExpressionReporter_h_
// SymbolicExpressionReporter.h
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//	AUTHOR: Ayman Habib
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
* Copyright (c)  2005, Stanford University. All rights reserved. 
* Use of the OpenSim software in source form is permitted provided that the following
* conditions are met:
* 	1. The software is used only for non-commercial research and education. It may not
*     be used in relation to any commercial activity.
* 	2. The software is not distributed or redistributed.  Software distribution is allowed 
*     only through https://simtk.org/home/opensim.
* 	3. Use of the OpenSim software or derivatives must be acknowledged in all publications,
*      presentations, or documents describing work in which OpenSim or derivatives are used.
* 	4. Credits to developers may not be removed from executables
*     created from modifications of the source.
* 	5. Modifications of source code must retain the above copyright notice, this list of
*     conditions and the following disclaimer. 
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
*  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
*  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
*  SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
*  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
*  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*  OR BUSINESS INTERRUPTION) OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
*  WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


//=============================================================================
// INCLUDES
//=============================================================================
#include <map>
#include <OpenSim.h>
#include "osimExpPluginDLL.h"


#ifdef SWIG
	#ifdef OSIMEXPPLUGIN_API
		#undef OSIMEXPPLUGIN_API
		#define OSIMEXPPLUGIN_API
	#endif
#endif
//=============================================================================
//=============================================================================
namespace OpenSim { 

/**
 * A class for recording the states of a model
 * during a simulation.
 *
 * @author Ayman Habib
 * @version 1.0
 */
class OSIMEXPPLUGIN_API SymbolicExpressionReporter : public Analysis {
OpenSim_DECLARE_CONCRETE_OBJECT(SymbolicExpressionReporter, Analysis);

//=============================================================================
// DATA
//=============================================================================
private:
	std::map<std::string, double> _variables;


protected:
	/** Expression that's a function of state variables and primitive model properties. */
	PropertyStr _expressionStrProp;
	std::string& _expressionStr;

	/** States storage. */
	Storage _resultStore;

//=============================================================================
// METHODS
//=============================================================================
public:
	SymbolicExpressionReporter(Model *aModel=0);
	SymbolicExpressionReporter(const std::string &aFileName);
	// Copy constrctor and virtual copy 
	SymbolicExpressionReporter(const SymbolicExpressionReporter &aObject);

	virtual ~SymbolicExpressionReporter();
private:
	void setNull();
	void constructDescription();
	void constructColumnLabels();
	void setupStorage();
	void setupProperties();

public:
	//--------------------------------------------------------------------------
	// OPERATORS
	//--------------------------------------------------------------------------
#ifndef SWIG
	SymbolicExpressionReporter& operator=(const SymbolicExpressionReporter &aRporter);
#endif
	//--------------------------------------------------------------------------
	// GET AND SET
	//--------------------------------------------------------------------------
	// STORAGE
	const Storage& getResultStorage() const
	{
		return _resultStore;
	};
	Storage& updResultStorage()
	{
		return _resultStore;
	}
	//--------------------------------------------------------------------------
	// ANALYSIS
	//--------------------------------------------------------------------------
#ifndef SWIG
	virtual int
        begin(SimTK::State& s );
    virtual int
        step(const SimTK::State& s, int setNumber );
    virtual int
        end(SimTK::State& s );
protected:
    virtual int
        record(const SimTK::State& s );
#endif
	//--------------------------------------------------------------------------
	// IO
	//--------------------------------------------------------------------------
public:
	virtual int
		printResults(const std::string &aBaseName,const std::string &aDir="",
		double aDT=-1.0,const std::string &aExtension=".sto");

//=============================================================================
};	// END of class SymbolicExpressionReporter

}; //namespace
//=============================================================================
//=============================================================================


#endif // #ifndef __SymbolicExpressionReporter_h__
