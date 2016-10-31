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

require 'fileutils'

RESULTS_FILE = 'data/solver-perf.results'.freeze
DATA_FILE = 'data/solver-perf-%%MOL%%.data'.freeze
PLOT_FILE_TPL = 'data/gnuplot_histogram.gnu'.freeze

DATA_SEPARATOR = "\t".freeze
HEADER_SEPARATOR = ':'.freeze

def generate_plot(data_line)
  raise 'Found empty data line!' if data_line.nil? || data_line.empty?
  data = generate_plot_data(*data_line.split(HEADER_SEPARATOR))

  plot_template = File.read(PLOT_FILE_TPL)
  plot_template.gsub!('%%YMAX%%', data[:ymax].to_s)
  plot_template.gsub!('%%YMIN%%', data[:ymin].to_s)
  plot_template.gsub!('%%HEADER%%', data[:header])
  plot_template.gsub!('%%INPUT_FILE%%', data[:path])
  plot_template.gsub!('%%OUTPUT_FILE%%', "images/solver-perf-#{data[:header]}.png")

  output_gnuplot_file = "images/solver-perf-#{data[:header]}.gnu"

  File.open(output_gnuplot_file, 'w') do |file|
    file.write plot_template
    file.flush
  end

  `gnuplot #{output_gnuplot_file}`

  FileUtils.rm output_gnuplot_file
  FileUtils.rm data[:path]
end

def generate_plot_data(header, line)
  count = 1
  ymax = ymin = 0

  of = File.open(DATA_FILE.gsub('%%MOL%%', header.strip), 'w')
  line.strip.split(DATA_SEPARATOR).each do |point|
    of.write "#{count} #{point}\n"
    ymax = point.to_i if point.to_i > ymax
    ymin = point.to_i if count == 1
    ymin = point.to_i if point.to_i < ymin
    count += 1
  end
  of.flush
  of.close

  { header: header, path: of.path, ymin: (ymin/2).floor, ymax: ymax * 2 }
end

##########################
## Main
##########################

raise "#{RESULTS_FILE} is not readable!" unless File.readable?(RESULTS_FILE)
raise "#{PLOT_FILE_TPL} is not readable!" unless File.readable?(PLOT_FILE_TPL)

File.open(RESULTS_FILE, 'r') do |data_file|
  data_file.each_line { |data_line| generate_plot(data_line) }
end
