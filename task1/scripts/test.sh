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

TEST_RUNS=20

cd "$SOLVER_DIR"
for MOLECULE in $(ls ./data/*.mol); do
	SOLVER_CMD="./eem_solver_proteins ${SOLVER_DIR}${MOLECULE} ${SOLVER_DIR}params_out.txt 0 2>&1 1>/dev/null"

	MOLECULE=${MOLECULE%.mol}
	for RUN in $(seq 1 $TEST_RUNS); do
		eval "/usr/bin/time -o ${REPORT_DIR}${MOLECULE##*/} -a -f \"%E\" ${SOLVER_CMD}"
	done
done
