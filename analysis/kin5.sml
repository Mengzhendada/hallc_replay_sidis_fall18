<Request>
  <Email email="shuojia@jlab.org" request="false" job="true"/>
  <Project name="c-comm2017"/>
  <Track  name="reconstruction"/>
  <Name   name="kingroup5"/>
  <OS     name="centos7"/>
  <Memory space="3" unit="GB"/>
  <List name="runs">
6111
6115
6124
6136

  </List>
  <ForEach list="runs">
    <Job>
      <Input src="mss:/mss/hallc/spring17/raw/coin_all_0${runs}.dat" dest="coin_all_0${runs}.dat"/>
      <!-- Properties overridden here -->
      <Command><![CDATA[
/bin/bash <<EOF
source /home/shuojia/.bashrc
cd /group/c-csv/shuo/replay/


hcana -q "scripts/replay_production_coin_hElec_pProt.C(${runs},-1)" 

EOF
        ]]></Command>
    </Job>
  </ForEach> 

</Request>

