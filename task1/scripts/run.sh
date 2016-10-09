#!/bin/bash

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

# Locate script directory
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
SOLVER_DIR="${SCRIPT_DIR}/../src/solver/"
REPORT_DIR="${SCRIPT_DIR}/../report/"

# Init
. ${SCRIPT_DIR}/init.sh

# Stage
. ${SCRIPT_DIR}/stage.sh

# Test
. ${SCRIPT_DIR}/test.sh

# Clean-up
. ${SCRIPT_DIR}/clean.sh
