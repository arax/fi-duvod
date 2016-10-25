#!/usr/bin/env ruby

#
#
#

RESULTS_FILE = 'data/solver-perf.results'.freeze
DATA_FILE = 'data/solver-perf-%%MOL%%.data'.freeze
PLOT_FILE_TPL = 'data/gnuplot_histogram.gnu'.freeze

DATA_SEPARATOR = "\t"
HEADER_SEPARATOR = ':'
HEADER_FORMAT = /(?<prefix>.+)_(?<size>\d+)/

def generate_plot(data_line)
  return if data_line.nil? || data_line.empty?
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
  `rm #{output_gnuplot_file}`
  `rm #{data[:path]}`
end

def generate_plot_data(header, line)
  count = 1
  ymax = 0
  ymin = 0

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

exit 1 unless File.readable?(RESULTS_FILE)
exit 2 unless File.readable?(PLOT_FILE_TPL)

File.open(RESULTS_FILE, 'r') do |data_file|
  data_file.each_line { |data_line| generate_plot(data_line) }
end
