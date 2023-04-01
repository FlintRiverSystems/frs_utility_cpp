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
		stage('build library')
		{
			steps
			{
				dir('frs_utility_cpp')
				{
					bat 'build.cmd'
				}
			}
		}
		stage('build tests')
		{
			steps
			{
				dir('frs_utility_cpp')
				{
					bat 'build_tests.cmd'
				}
			}
		}
		stage('test')
		{
			steps
			{
				dir('frs_utility_cpp')
				{
					bat 'run_tests.cmd'
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
	
