#!/usr/bin/env ruby

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

require 'erb'
require 'fileutils'

RESULTS_FILE = 'data/solver-perf.results'.freeze

DATA_SEPARATOR = "\t".freeze
HEADER_SEPARATOR = ':'.freeze
HEADER_FORMAT = /(?<prefix>.+)_(?<size>\d+)/
MEASUREMENTS_PER_LINE = 20

TEX_TABLE_TPL = %q!
\begin{center}
  \begin{tabular}{ | c | c | }
    \hline
    \textbf{Molecule size} & \textbf{Time in [ms] (p = 0.68)} \\\ \hline
    \hline
    <% lines.each do |line| %>
    <%= [line[0], "#{'%.2f' % line[1]} $\\\pm$ #{'%.2f' % line[2]}"].join(' & ') %> \\\ \hline
    <% end %>
  \end{tabular}
\end{center}

!.freeze

PLAIN_TABLE_TPL = %q!
#<%= %w(MSize Time[ms]).join("\t") %>
<%= "\n" %>
<% lines.each do |line| %>
<%= [line[0], line[1]].join("\t") %>
<%= "\n" %>
<% end %>

!

R_TABLE_TPL = %q!
Size = c(<%= lines.collect { |i| i[0] }.join(", ") %>)
Time = c(<%= lines.collect { |i| i[1] }.join(", ") %>)

!

# Fake table (TODO: fix!)
CORR_MAP = {
  19 => {    # these values are taken from n = 18 !!!
    68 => 1.0292,
    99 => 2.8784
  }
}

def generate_table(data_file)
  lines = calculate_lines(data_file)

  tpl_type =  case ARGV[0]
              when 'latex', 'tex'
                TEX_TABLE_TPL
              when 'r'
                R_TABLE_TPL
              when 'plain', 'gnuplot', '', nil
                PLAIN_TABLE_TPL
              else
                raise "Unknown output type #{ARGV[0].inspect}!"
              end

  template = ERB.new(tpl_type, 3, '>')
  template.result(binding)
end

def calculate_lines(data_file)
  lines = []
  data_file.each_line do |data_line|
    lines << calculate_line(data_line)
  end
  lines
end

def calculate_line(data_line)
  raise 'Found empty data line!' if data_line.nil? || data_line.empty?
  result = []

  header, data = data_line.split(HEADER_SEPARATOR)
  result[0] = HEADER_FORMAT.match(header.strip)[:size].to_i

  measurements = data.strip.split(DATA_SEPARATOR).collect { |d| d.strip.to_i }
  raise "Need #{MEASUREMENTS_PER_LINE} values per line!" unless measurements.count == MEASUREMENTS_PER_LINE

  avg = measurements.reduce(:+).to_f / MEASUREMENTS_PER_LINE
  std_dev_per_m = Math.sqrt( measurements.collect { |m| (avg - m)**2 }.reduce(:+) / (MEASUREMENTS_PER_LINE - 1) )
  std_dev_avg = std_dev_per_m / Math.sqrt(MEASUREMENTS_PER_LINE)

  corr_std_dev_avg_68 = std_dev_avg * CORR_MAP[MEASUREMENTS_PER_LINE - 1][68]
  corr_std_dev_avg_99 = std_dev_avg * CORR_MAP[MEASUREMENTS_PER_LINE - 1][99]

  result[1] = avg.round(2)
  result[2] = corr_std_dev_avg_68.round(2)
  result[3] = corr_std_dev_avg_99.round(2)

  result
end

##########################
## Main
##########################

raise "#{RESULTS_FILE} is not readable!" unless File.readable?(RESULTS_FILE)
puts File.open(RESULTS_FILE, 'r') { |data_file| generate_table(data_file) }
