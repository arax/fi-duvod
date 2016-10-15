FROM       gcc:6.2.0

MAINTAINER Boris Parak <parak@cesnet.cz>
LABEL      name="solver-perf" version="1.0" license="Apache License, Version 2.0, January 2004"

COPY       . /opt/solver-perf
WORKDIR    /opt/solver-perf

RUN        apt-get update && apt-get install time

CMD        /opt/solver-perf/scripts/run.sh
