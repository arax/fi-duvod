# -------------------------------------------------------------------------- #
# Licensed under the Apache License, Version 2.0 (the "License"); you may    #
# not use this file except in compliance with the License. You may obtain    #
# a copy of the License at                                                   #
#                                                                            #
# http://www.apache.org/licenses/LICENSE-2.0                                 #
#                                                                            #
# Unless required by applicable law or agreed to in writing, software        #
# distributed under the License is distributed on an "AS IS" BASIS,          #
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   #
# See the License for the specific language governing permissions and        #
# limitations under the License.                                             #
#--------------------------------------------------------------------------- #

if [ ! -d "$SOLVER_DIR" ]; then
	printf "Solver directory not found as $SOLVER_DIR\n"
	exit 1
fi

if [ ! -d "$REPORT_DIR" ]; then
	printf "Report directory not found as $REPORT_DIR\n"
	exit 2
fi

MAKE_PATH=`which make`
if [ ! -x "$MAKE_PATH" ]; then
	printf "Make executable not found\n"
	exit 3
fi
export MAKE_PATH

GCC_PATH=`which gcc`
if [ ! -x "$GCC_PATH" ]; then
	printf "GCC executable not found\n"
	exit 4
fi
export GCC_PATH
