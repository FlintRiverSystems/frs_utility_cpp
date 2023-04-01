pipeline
{
	agent 
	{
		label 'VS2017'
	}

	options 
	{
		skipDefaultCheckout()
	}

	triggers
	{
		cron('@daily')
	}

	stages
	{
		stage('prep')
		{
			steps
			{
				deleteDir()

				dir('frs_utility_cpp')
				{
					checkout scm
				}
			}
		}

		stage('build')
		{
			steps
			{
				dir('FRS_Utility_CPP')
				{
					bat 'build.cmd'
				}
			}
		}
		stage('test')
		{
			steps
			{
				dir('FRS_Utility_CPP')
				{
					bat 'test.cmd'
				}
			}
		}
	}

	post
	{
		success 
		{
			mail body: 'EOM', from: 'jenkins@flintriversystems.com', subject: "Job ${env.JOB_NAME} (${env.BUILD_NUMBER}) success", to: 'reporting@flintriversystems.com'
		}
		failure 
		{
			mail body: 'EOM', from: 'jenkins@flintriversystems.com', subject: "Job ${env.JOB_NAME} (${env.BUILD_NUMBER}) failed", to: 'reporting@flintriversystems.com'
		}
	}
}
	
